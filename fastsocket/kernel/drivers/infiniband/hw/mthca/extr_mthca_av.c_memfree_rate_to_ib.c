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
#define  MTHCA_RATE_MEMFREE_EIGHTH 131 
#define  MTHCA_RATE_MEMFREE_FULL 130 
#define  MTHCA_RATE_MEMFREE_HALF 129 
#define  MTHCA_RATE_MEMFREE_QUARTER 128 
 int mult_to_ib_rate (int) ; 

__attribute__((used)) static enum ib_rate memfree_rate_to_ib(u8 mthca_rate, u8 port_rate)
{
	switch (mthca_rate) {
	case MTHCA_RATE_MEMFREE_EIGHTH:
		return mult_to_ib_rate(port_rate >> 3);
	case MTHCA_RATE_MEMFREE_QUARTER:
		return mult_to_ib_rate(port_rate >> 2);
	case MTHCA_RATE_MEMFREE_HALF:
		return mult_to_ib_rate(port_rate >> 1);
	case MTHCA_RATE_MEMFREE_FULL:
	default:
		return mult_to_ib_rate(port_rate);
	}
}