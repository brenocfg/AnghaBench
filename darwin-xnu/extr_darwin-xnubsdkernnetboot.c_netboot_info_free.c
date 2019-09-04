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
struct netboot_info {int mount_point_length; int server_name_length; int image_path_length; int second_image_path_length; struct netboot_info* second_image_path; struct netboot_info* image_path; struct netboot_info* server_name; struct netboot_info* mount_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct netboot_info*,int) ; 

__attribute__((used)) static void 
netboot_info_free(struct netboot_info * * info_p)
{
    struct netboot_info * info = *info_p;

    if (info) {
	if (info->mount_point) {
	    kfree(info->mount_point, info->mount_point_length);
	}
	if (info->server_name) {
	    kfree(info->server_name, info->server_name_length);
	}
	if (info->image_path) {
	    kfree(info->image_path, info->image_path_length);
	}
	if (info->second_image_path) {
	    kfree(info->second_image_path, info->second_image_path_length);
	}
	kfree(info, sizeof(*info));
    }
    *info_p = NULL;
    return;
}