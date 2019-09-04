#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * second_image_path; int /*<<< orphan*/ * image_path; } ;

/* Variables and functions */
 TYPE_1__* S_netboot_info_p ; 
 int imageboot_mount_image (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netboot_info_free (TYPE_1__**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
netboot_setup()
{
    int 	error = 0;

    if (S_netboot_info_p == NULL
	|| S_netboot_info_p->image_path == NULL) {
	goto done;
    }
    printf("netboot_setup: calling imageboot_mount_image\n");
    error = imageboot_mount_image(S_netboot_info_p->image_path, -1);
    if (error != 0) {
	printf("netboot: failed to mount root image, %d\n", error);
    }
    else if (S_netboot_info_p->second_image_path != NULL) {
	error = imageboot_mount_image(S_netboot_info_p->second_image_path, 0);
	if (error != 0) {
	    printf("netboot: failed to mount second root image, %d\n", error);
	}
    }

 done:
    netboot_info_free(&S_netboot_info_p);
    return (error);
}