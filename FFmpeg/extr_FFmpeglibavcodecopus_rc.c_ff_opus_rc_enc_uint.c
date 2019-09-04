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
 int FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_opus_rc_put_raw (int /*<<< orphan*/ *,int,int const) ; 
 scalar_t__ opus_ilog (int) ; 
 int /*<<< orphan*/  opus_rc_enc_update (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

void ff_opus_rc_enc_uint(OpusRangeCoder *rc, uint32_t val, uint32_t size)
{
    const int ps = FFMAX(opus_ilog(size - 1) - 8, 0);
    opus_rc_enc_update(rc, val >> ps, (val >> ps) + 1, ((size - 1) >> ps) + 1, 0);
    ff_opus_rc_put_raw(rc, val, ps);
}