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
 unsigned int MSeries_PFI_Filter_Select_Mask (unsigned int) ; 

__attribute__((used)) static inline unsigned MSeries_PFI_Filter_Select_Bits(unsigned channel,
						      unsigned filter)
{
	return (filter << (channel *
			   2)) & MSeries_PFI_Filter_Select_Mask(channel);
}