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
typedef  int /*<<< orphan*/  OpusRangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  opus_rc_enc_update (int /*<<< orphan*/ *,int,int,int,int) ; 

void ff_opus_rc_enc_log(OpusRangeCoder *rc, int val, uint32_t bits)
{
    bits = (1 << bits) - 1;
    opus_rc_enc_update(rc, (!!val)*bits, bits + !!val, bits + 1, 1);
}