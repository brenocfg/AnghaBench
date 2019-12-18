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
struct esp {scalar_t__ dma_regs; } ;

/* Variables and functions */
 int R4030_ADDR_INTR ; 
 int R4030_MEM_INTR ; 
 int vdma_get_enable (int) ; 

__attribute__((used)) static int jazz_esp_dma_error(struct esp *esp)
{
	u32 enable = vdma_get_enable((int)esp->dma_regs);

	if (enable & (R4030_MEM_INTR|R4030_ADDR_INTR))
		return 1;

	return 0;
}