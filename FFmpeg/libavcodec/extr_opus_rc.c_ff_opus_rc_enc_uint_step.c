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
 int /*<<< orphan*/  opus_rc_enc_update (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

void ff_opus_rc_enc_uint_step(OpusRangeCoder *rc, uint32_t val, int k0)
{
    const uint32_t a = val <= k0, b = 2*a + 1;
    k0 = (k0 + 1) << 1;
    val = b*(val + k0) - 3*a*k0;
    opus_rc_enc_update(rc, val, val + b, (k0 << 1) - 1, 0);
}