#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {scalar_t__ lcd_phys_start; scalar_t__ lcd_virt_start; } ;
struct TYPE_4__ {int fb_type; int fb_length; scalar_t__ addr_offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_2__ dum_data ; 
 TYPE_1__* fb_addr ; 

int pnx4008_get_fb_addresses(int fb_type, void **virt_addr,
			     dma_addr_t *phys_addr, int *fb_length)
{
	int i;
	int ret = -1;
	for (i = 0; i < ARRAY_SIZE(fb_addr); i++)
		if (fb_addr[i].fb_type == fb_type) {
			*virt_addr = (void *)(dum_data.lcd_virt_start +
					fb_addr[i].addr_offset);
			*phys_addr =
			    dum_data.lcd_phys_start + fb_addr[i].addr_offset;
			*fb_length = fb_addr[i].fb_length;
			ret = 0;
			break;
		}

	return ret;
}