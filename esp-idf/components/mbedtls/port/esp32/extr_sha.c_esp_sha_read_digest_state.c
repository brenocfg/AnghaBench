#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ esp_sha_type ;
typedef  int /*<<< orphan*/  SemaphoreHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_INTERRUPT_DISABLE () ; 
 int /*<<< orphan*/  DPORT_INTERRUPT_RESTORE () ; 
 int DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int DPORT_SEQUENCE_REG_READ (int) ; 
 scalar_t__ SHA2_384 ; 
 scalar_t__ SHA2_512 ; 
 int /*<<< orphan*/  SHA_BUSY_REG (scalar_t__) ; 
 int /*<<< orphan*/  SHA_LOAD_REG (scalar_t__) ; 
 scalar_t__ SHA_TEXT_BASE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_dport_access_read_buffer (int*,int,int) ; 
 int /*<<< orphan*/  esp_sha_lock_memory_block () ; 
 int /*<<< orphan*/  esp_sha_unlock_memory_block () ; 
 int /*<<< orphan*/  esp_sha_wait_idle () ; 
 int /*<<< orphan*/ * sha_get_engine_state (scalar_t__) ; 
 int sha_length (scalar_t__) ; 
 scalar_t__ uxSemaphoreGetCount (int /*<<< orphan*/ *) ; 

void esp_sha_read_digest_state(esp_sha_type sha_type, void *digest_state)
{
    uint32_t *digest_state_words = NULL;
    uint32_t *reg_addr_buf = NULL;
    uint32_t word_len = sha_length(sha_type)/4;
#ifndef NDEBUG
    {
        SemaphoreHandle_t *engine_state = sha_get_engine_state(sha_type);
        assert(uxSemaphoreGetCount(engine_state) == 0 &&
               "SHA engine should be locked" );
    }
#endif

    // preemptively do this before entering the critical section, then re-check once in it
    esp_sha_wait_idle();

    esp_sha_lock_memory_block();

    esp_sha_wait_idle();

    DPORT_REG_WRITE(SHA_LOAD_REG(sha_type), 1);
    while(DPORT_REG_READ(SHA_BUSY_REG(sha_type)) == 1) { }
    digest_state_words = (uint32_t *)digest_state;
    reg_addr_buf = (uint32_t *)(SHA_TEXT_BASE);
    if(sha_type == SHA2_384 || sha_type == SHA2_512) {
        /* for these ciphers using 64-bit states, swap each pair of words */
        DPORT_INTERRUPT_DISABLE(); // Disable interrupt only on current CPU.
        for(int i = 0; i < word_len; i += 2) {
            digest_state_words[i+1] = DPORT_SEQUENCE_REG_READ((uint32_t)&reg_addr_buf[i]);
            digest_state_words[i]   = DPORT_SEQUENCE_REG_READ((uint32_t)&reg_addr_buf[i+1]);
        }
        DPORT_INTERRUPT_RESTORE(); // restore the previous interrupt level
    } else {
        esp_dport_access_read_buffer(digest_state_words, (uint32_t)&reg_addr_buf[0], word_len);
    }
    esp_sha_unlock_memory_block();

    /* Fault injection check: verify SHA engine actually ran,
       state is not all zeroes.
    */
    for (int i = 0; i < word_len; i++) {
        if (digest_state_words[i] != 0) {
            return;
        }
    }
    abort(); // SHA peripheral returned all zero state, probably due to fault injection
}