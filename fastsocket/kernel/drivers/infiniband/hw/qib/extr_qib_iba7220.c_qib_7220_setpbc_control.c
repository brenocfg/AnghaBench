#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
struct qib_pportdata {size_t delay_mult; TYPE_1__* cpspec; } ;
struct TYPE_2__ {size_t last_delay_mult; } ;

/* Variables and functions */
 size_t PBC_7220_VL15_SEND_CTRL ; 
 size_t* ib_rate_to_delay ; 

__attribute__((used)) static u32 qib_7220_setpbc_control(struct qib_pportdata *ppd, u32 plen,
				   u8 srate, u8 vl)
{
	u8 snd_mult = ppd->delay_mult;
	u8 rcv_mult = ib_rate_to_delay[srate];
	u32 ret = ppd->cpspec->last_delay_mult;

	ppd->cpspec->last_delay_mult = (rcv_mult > snd_mult) ?
		(plen * (rcv_mult - snd_mult) + 1) >> 1 : 0;

	/* Indicate VL15, if necessary */
	if (vl == 15)
		ret |= PBC_7220_VL15_SEND_CTRL;
	return ret;
}