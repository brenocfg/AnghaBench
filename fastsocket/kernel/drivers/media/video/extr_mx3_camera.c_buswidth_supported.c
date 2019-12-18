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
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct mx3_camera_dev {int platform_flags; } ;

/* Variables and functions */
 int MX3_CAMERA_DATAWIDTH_10 ; 
 int MX3_CAMERA_DATAWIDTH_15 ; 
 int MX3_CAMERA_DATAWIDTH_4 ; 
 int MX3_CAMERA_DATAWIDTH_8 ; 

__attribute__((used)) static bool buswidth_supported(struct soc_camera_host *ici, int depth)
{
	struct mx3_camera_dev *mx3_cam = ici->priv;

	switch (depth) {
	case 4:
		return !!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_4);
	case 8:
		return !!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_8);
	case 10:
		return !!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_10);
	case 15:
		return !!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_15);
	}
	return false;
}