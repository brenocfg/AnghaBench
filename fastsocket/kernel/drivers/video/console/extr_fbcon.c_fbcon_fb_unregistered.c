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
 int FB_MAX ; 
 int* con2fb_map ; 
 int /*<<< orphan*/  fb_con ; 
 int first_fb_vc ; 
 int info_idx ; 
 int last_fb_vc ; 
 int /*<<< orphan*/  num_registered_fb ; 
 int primary_device ; 
 int /*<<< orphan*/ ** registered_fb ; 
 int /*<<< orphan*/  unregister_con_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fbcon_fb_unregistered(struct fb_info *info)
{
	int i, idx;

	idx = info->node;
	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		if (con2fb_map[i] == idx)
			con2fb_map[i] = -1;
	}

	if (idx == info_idx) {
		info_idx = -1;

		for (i = 0; i < FB_MAX; i++) {
			if (registered_fb[i] != NULL) {
				info_idx = i;
				break;
			}
		}
	}

	if (info_idx != -1) {
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map[i] == -1)
				con2fb_map[i] = info_idx;
		}
	}

	if (primary_device == idx)
		primary_device = -1;

	if (!num_registered_fb)
		unregister_con_driver(&fb_con);

	return 0;
}