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
struct channel_subsystem {int cm_enabled; void* cub_addr2; void* cub_addr1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __chsc_do_secm (struct channel_subsystem*,int,void*) ; 
 int chsc_add_cmg_attr (struct channel_subsystem*) ; 
 int /*<<< orphan*/  chsc_remove_cmg_attr (struct channel_subsystem*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
chsc_secm(struct channel_subsystem *css, int enable)
{
	void  *secm_area;
	int ret;

	secm_area = (void *)get_zeroed_page(GFP_KERNEL |  GFP_DMA);
	if (!secm_area)
		return -ENOMEM;

	if (enable && !css->cm_enabled) {
		css->cub_addr1 = (void *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
		css->cub_addr2 = (void *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
		if (!css->cub_addr1 || !css->cub_addr2) {
			free_page((unsigned long)css->cub_addr1);
			free_page((unsigned long)css->cub_addr2);
			free_page((unsigned long)secm_area);
			return -ENOMEM;
		}
	}
	ret = __chsc_do_secm(css, enable, secm_area);
	if (!ret) {
		css->cm_enabled = enable;
		if (css->cm_enabled) {
			ret = chsc_add_cmg_attr(css);
			if (ret) {
				memset(secm_area, 0, PAGE_SIZE);
				__chsc_do_secm(css, 0, secm_area);
				css->cm_enabled = 0;
			}
		} else
			chsc_remove_cmg_attr(css);
	}
	if (!css->cm_enabled) {
		free_page((unsigned long)css->cub_addr1);
		free_page((unsigned long)css->cub_addr2);
	}
	free_page((unsigned long)secm_area);
	return ret;
}