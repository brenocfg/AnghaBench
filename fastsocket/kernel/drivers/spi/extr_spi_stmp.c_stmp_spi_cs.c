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
typedef  int u32 ;

/* Variables and functions */
 int BM_SSP_CTRL0_WAIT_FOR_CMD ; 
 int BM_SSP_CTRL0_WAIT_FOR_IRQ ; 

__attribute__((used)) static inline u32 stmp_spi_cs(unsigned cs)
{
	return  ((cs & 1) ? BM_SSP_CTRL0_WAIT_FOR_CMD : 0) |
		((cs & 2) ? BM_SSP_CTRL0_WAIT_FOR_IRQ : 0);
}