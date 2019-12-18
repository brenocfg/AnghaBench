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
#define  IB_RATE_100_GBPS 144 
#define  IB_RATE_10_GBPS 143 
#define  IB_RATE_112_GBPS 142 
#define  IB_RATE_120_GBPS 141 
#define  IB_RATE_14_GBPS 140 
#define  IB_RATE_168_GBPS 139 
#define  IB_RATE_200_GBPS 138 
#define  IB_RATE_20_GBPS 137 
#define  IB_RATE_25_GBPS 136 
#define  IB_RATE_2_5_GBPS 135 
#define  IB_RATE_300_GBPS 134 
#define  IB_RATE_30_GBPS 133 
#define  IB_RATE_40_GBPS 132 
#define  IB_RATE_56_GBPS 131 
#define  IB_RATE_5_GBPS 130 
#define  IB_RATE_60_GBPS 129 
#define  IB_RATE_80_GBPS 128 

int ib_rate_to_mbps(enum ib_rate rate)
{
	switch (rate) {
	case IB_RATE_2_5_GBPS: return 2500;
	case IB_RATE_5_GBPS:   return 5000;
	case IB_RATE_10_GBPS:  return 10000;
	case IB_RATE_20_GBPS:  return 20000;
	case IB_RATE_30_GBPS:  return 30000;
	case IB_RATE_40_GBPS:  return 40000;
	case IB_RATE_60_GBPS:  return 60000;
	case IB_RATE_80_GBPS:  return 80000;
	case IB_RATE_120_GBPS: return 120000;
	case IB_RATE_14_GBPS:  return 14062;
	case IB_RATE_56_GBPS:  return 56250;
	case IB_RATE_112_GBPS: return 112500;
	case IB_RATE_168_GBPS: return 168750;
	case IB_RATE_25_GBPS:  return 25781;
	case IB_RATE_100_GBPS: return 103125;
	case IB_RATE_200_GBPS: return 206250;
	case IB_RATE_300_GBPS: return 309375;
	default:	       return -1;
	}
}