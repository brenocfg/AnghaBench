#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {struct TYPE_9__* K1; struct TYPE_9__* K2; struct TYPE_9__* iv; int /*<<< orphan*/  sched; } ;
typedef  TYPE_1__* TCCmacState_t ;
typedef  int /*<<< orphan*/  TCAesKeySched_t ;

/* Variables and functions */
 int TC_AES_BLOCK_SIZE ; 
 int TC_CRYPTO_FAIL ; 
 int TC_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  _set (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gf_double (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  tc_aes128_set_encrypt_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tc_aes_encrypt (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_cmac_init (TYPE_1__*) ; 

int tc_cmac_setup(TCCmacState_t s, const uint8_t *key, TCAesKeySched_t sched)
{

    /* input sanity check: */
    if (s == (TCCmacState_t) 0 ||
            key == (const uint8_t *) 0) {
        return TC_CRYPTO_FAIL;
    }

    /* put s into a known state */
    _set(s, 0, sizeof(*s));
    s->sched = sched;

    /* configure the encryption key used by the underlying block cipher */
    tc_aes128_set_encrypt_key(s->sched, key);

    /* compute s->K1 and s->K2 from s->iv using s->keyid */
    _set(s->iv, 0, TC_AES_BLOCK_SIZE);
    tc_aes_encrypt(s->iv, s->iv, s->sched);
    gf_double (s->K1, s->iv);
    gf_double (s->K2, s->K1);

    /* reset s->iv to 0 in case someone wants to compute now */
    tc_cmac_init(s);

    return TC_CRYPTO_SUCCESS;
}