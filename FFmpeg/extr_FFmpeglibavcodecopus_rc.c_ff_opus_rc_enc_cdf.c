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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  opus_rc_enc_update (int /*<<< orphan*/ *,int,int const,int const,int) ; 

void ff_opus_rc_enc_cdf(OpusRangeCoder *rc, int val, const uint16_t *cdf)
{
    opus_rc_enc_update(rc, (!!val)*cdf[val], cdf[val + 1], cdf[0], 1);
}