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
typedef  int u8 ;
typedef  enum ib_rate { ____Placeholder_ib_rate } ib_rate ;

/* Variables and functions */
 int IB_RATE_10_GBPS ; 
 int IB_RATE_2_5_GBPS ; 
 int IB_RATE_5_GBPS ; 
#define  MTHCA_RATE_TAVOR_1X 130 
#define  MTHCA_RATE_TAVOR_1X_DDR 129 
#define  MTHCA_RATE_TAVOR_4X 128 
 int mult_to_ib_rate (int) ; 

__attribute__((used)) static enum ib_rate tavor_rate_to_ib(u8 mthca_rate, u8 port_rate)
{
	switch (mthca_rate) {
	case MTHCA_RATE_TAVOR_1X:     return IB_RATE_2_5_GBPS;
	case MTHCA_RATE_TAVOR_1X_DDR: return IB_RATE_5_GBPS;
	case MTHCA_RATE_TAVOR_4X:     return IB_RATE_10_GBPS;
	default:		      return mult_to_ib_rate(port_rate);
	}
}