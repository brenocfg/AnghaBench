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
typedef  enum ib_rate { ____Placeholder_ib_rate } ib_rate ;

/* Variables and functions */
#define  IB_RATE_10_GBPS 136 
#define  IB_RATE_120_GBPS 135 
#define  IB_RATE_20_GBPS 134 
#define  IB_RATE_2_5_GBPS 133 
#define  IB_RATE_30_GBPS 132 
#define  IB_RATE_40_GBPS 131 
#define  IB_RATE_5_GBPS 130 
#define  IB_RATE_60_GBPS 129 
#define  IB_RATE_80_GBPS 128 

int ib_rate_to_mult(enum ib_rate rate)
{
	switch (rate) {
	case IB_RATE_2_5_GBPS: return  1;
	case IB_RATE_5_GBPS:   return  2;
	case IB_RATE_10_GBPS:  return  4;
	case IB_RATE_20_GBPS:  return  8;
	case IB_RATE_30_GBPS:  return 12;
	case IB_RATE_40_GBPS:  return 16;
	case IB_RATE_60_GBPS:  return 24;
	case IB_RATE_80_GBPS:  return 32;
	case IB_RATE_120_GBPS: return 48;
	default:	       return -1;
	}
}