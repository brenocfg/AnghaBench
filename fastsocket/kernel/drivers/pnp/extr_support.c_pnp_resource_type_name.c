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
struct resource {int dummy; } ;

/* Variables and functions */
#define  IORESOURCE_DMA 131 
#define  IORESOURCE_IO 130 
#define  IORESOURCE_IRQ 129 
#define  IORESOURCE_MEM 128 
 int pnp_resource_type (struct resource*) ; 

char *pnp_resource_type_name(struct resource *res)
{
	switch (pnp_resource_type(res)) {
	case IORESOURCE_IO:
		return "io";
	case IORESOURCE_MEM:
		return "mem";
	case IORESOURCE_IRQ:
		return "irq";
	case IORESOURCE_DMA:
		return "dma";
	}
	return NULL;
}