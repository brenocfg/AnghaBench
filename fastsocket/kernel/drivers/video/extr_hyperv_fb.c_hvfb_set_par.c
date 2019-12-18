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
struct hv_device {int dummy; } ;
struct fb_info {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct hv_device* device_to_hv_device (int /*<<< orphan*/ ) ; 
 int synthvid_send_situ (struct hv_device*) ; 

__attribute__((used)) static int hvfb_set_par(struct fb_info *info)
{
	struct hv_device *hdev = device_to_hv_device(info->device);

	return synthvid_send_situ(hdev);
}