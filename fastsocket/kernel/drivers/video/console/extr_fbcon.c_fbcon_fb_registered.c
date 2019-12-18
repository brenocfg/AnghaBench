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
struct fb_info {int node; } ;

/* Variables and functions */
 int* con2fb_map_boot ; 
 int /*<<< orphan*/  fbcon_select_primary (struct fb_info*) ; 
 int fbcon_takeover (int) ; 
 int first_fb_vc ; 
 int info_idx ; 
 int last_fb_vc ; 
 int /*<<< orphan*/  set_con2fb_map (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fbcon_fb_registered(struct fb_info *info)
{
	int ret = 0, i, idx;

	idx = info->node;
	fbcon_select_primary(info);

	if (info_idx == -1) {
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map_boot[i] == idx) {
				info_idx = idx;
				break;
			}
		}

		if (info_idx != -1)
			ret = fbcon_takeover(1);
	} else {
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map_boot[i] == idx)
				set_con2fb_map(i, idx, 0);
		}
	}

	return ret;
}