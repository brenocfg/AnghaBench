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
 int IB_RATE_10_GBPS ; 
 int IB_RATE_20_GBPS ; 
 int IB_RATE_2_5_GBPS ; 
 int IB_RATE_5_GBPS ; 
 int IB_RATE_PORT_CURRENT ; 

__attribute__((used)) static enum ib_rate ipath_mult_to_ib_rate(unsigned mult)
{
	switch (mult) {
	case 8:  return IB_RATE_2_5_GBPS;
	case 4:  return IB_RATE_5_GBPS;
	case 2:  return IB_RATE_10_GBPS;
	case 1:  return IB_RATE_20_GBPS;
	default: return IB_RATE_PORT_CURRENT;
	}
}