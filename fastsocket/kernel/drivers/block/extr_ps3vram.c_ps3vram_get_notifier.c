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
typedef  void u32 ;

/* Variables and functions */
 int DMA_NOTIFIER_OFFSET_BASE ; 
 int DMA_NOTIFIER_SIZE ; 

__attribute__((used)) static u32 *ps3vram_get_notifier(void *reports, int notifier)
{
	return reports + DMA_NOTIFIER_OFFSET_BASE +
	       DMA_NOTIFIER_SIZE * notifier;
}