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
typedef  int u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int lmb_end_of_DRAM () ; 

__attribute__((used)) static int dma_direct_dma_supported(struct device *dev, u64 mask)
{
#ifdef CONFIG_PPC64
	/* Could be improved so platforms can set the limit in case
	 * they have limited DMA windows
	 */
	return mask >= (lmb_end_of_DRAM() - 1);
#else
	return 1;
#endif
}