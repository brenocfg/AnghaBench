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
#define  IB_RATE_10_GBPS 131 
#define  IB_RATE_20_GBPS 130 
#define  IB_RATE_2_5_GBPS 129 
#define  IB_RATE_5_GBPS 128 

unsigned ipath_ib_rate_to_mult(enum ib_rate rate)
{
	switch (rate) {
	case IB_RATE_2_5_GBPS: return 8;
	case IB_RATE_5_GBPS:   return 4;
	case IB_RATE_10_GBPS:  return 2;
	case IB_RATE_20_GBPS:  return 1;
	default:	       return 0;
	}
}