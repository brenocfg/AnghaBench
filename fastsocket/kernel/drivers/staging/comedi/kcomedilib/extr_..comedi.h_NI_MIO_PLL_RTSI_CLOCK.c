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

/* Variables and functions */
 int NI_MIO_PLL_RTSI0_CLOCK ; 

__attribute__((used)) static inline unsigned NI_MIO_PLL_RTSI_CLOCK(unsigned rtsi_channel) {
		return NI_MIO_PLL_RTSI0_CLOCK + rtsi_channel;
	}