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
 unsigned long sysctl_tcp_dma_copybreak ; 

__attribute__((used)) static inline void ioat_set_tcp_copy_break(unsigned long copybreak)
{
	#ifdef CONFIG_NET_DMA
	sysctl_tcp_dma_copybreak = copybreak;
	#endif
}