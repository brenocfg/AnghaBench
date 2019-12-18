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
 unsigned int tlb1_entry_num ; 
 unsigned int tlbcam_index ; 

__attribute__((used)) static inline unsigned int tlb1_max_shadow_size(void)
{
	return tlb1_entry_num - tlbcam_index;
}