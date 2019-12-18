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
typedef  int esp_sha_type ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHA_CONTINUE_REG ; 
 int /*<<< orphan*/  SHA_MODE_REG ; 
 scalar_t__ SHA_M_BASE ; 
 int /*<<< orphan*/  SHA_START_REG ; 
 int /*<<< orphan*/  block_length (int) ; 
 int /*<<< orphan*/  esp_sha_wait_idle () ; 
 int /*<<< orphan*/  memcpy_endianswap (void*,void const*,int /*<<< orphan*/ ) ; 

void esp_sha_block(esp_sha_type sha_type, const void *data_block, bool is_first_block)
{
    /* engine should be locked */

    REG_WRITE(SHA_MODE_REG, sha_type);

    /* ESP32C SHA unit can be loaded while previous block is processing */
    memcpy_endianswap((void *)SHA_M_BASE, data_block, block_length(sha_type));

    esp_sha_wait_idle();
    if (is_first_block) {
        REG_WRITE(SHA_START_REG, 1);
    } else {
        REG_WRITE(SHA_CONTINUE_REG, 1);
    }

    /* Note: deliberately not waiting for this operation to complete,
       as a performance tweak - delay waiting until the next time we need the SHA
       unit, instead.
    */
}