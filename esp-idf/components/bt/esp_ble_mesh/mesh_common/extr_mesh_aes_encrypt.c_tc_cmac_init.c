#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  countdown; scalar_t__ leftover_offset; int /*<<< orphan*/  leftover; int /*<<< orphan*/  iv; } ;
typedef  TYPE_1__* TCCmacState_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CALLS ; 
 int /*<<< orphan*/  TC_AES_BLOCK_SIZE ; 
 int TC_CRYPTO_FAIL ; 
 int TC_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  _set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tc_cmac_init(TCCmacState_t s)
{
    /* input sanity check: */
    if (s == (TCCmacState_t) 0) {
        return TC_CRYPTO_FAIL;
    }

    /* CMAC starts with an all zero initialization vector */
    _set(s->iv, 0, TC_AES_BLOCK_SIZE);

    /* and the leftover buffer is empty */
    _set(s->leftover, 0, TC_AES_BLOCK_SIZE);
    s->leftover_offset = 0;

    /* Set countdown to max number of calls allowed before re-keying: */
    s->countdown = MAX_CALLS;

    return TC_CRYPTO_SUCCESS;
}