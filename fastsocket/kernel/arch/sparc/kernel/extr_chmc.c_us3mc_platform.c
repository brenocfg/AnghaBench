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
 scalar_t__ cheetah ; 
 scalar_t__ cheetah_plus ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static inline bool us3mc_platform(void)
{
	if (tlb_type == cheetah || tlb_type == cheetah_plus)
		return true;
	return false;
}