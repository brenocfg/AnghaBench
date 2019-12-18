#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int key; int device_path_info_length; } ;
struct edd_info {TYPE_1__ params; } ;
struct edd_device {int dummy; } ;

/* Variables and functions */
 struct edd_info* edd_dev_get_info (struct edd_device*) ; 

__attribute__((used)) static int
edd_has_edd30(struct edd_device *edev)
{
	struct edd_info *info;
	int i;
	u8 csum = 0;

	if (!edev)
		return 0;
	info = edd_dev_get_info(edev);
	if (!info)
		return 0;

	if (!(info->params.key == 0xBEDD || info->params.key == 0xDDBE)) {
		return 0;
	}


	/* We support only T13 spec */
	if (info->params.device_path_info_length != 44)
		return 0;

	for (i = 30; i < info->params.device_path_info_length + 30; i++)
		csum += *(((u8 *)&info->params) + i);

	if (csum)
		return 0;

	return 1;
}