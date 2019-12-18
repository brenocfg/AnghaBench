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
struct TYPE_2__ {int info_flags; } ;
struct edd_info {TYPE_1__ params; } ;
struct edd_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT ; 
 int EDD_INFO_GEOMETRY_VALID ; 
 int EDD_INFO_LOCKABLE ; 
 int EDD_INFO_MEDIA_CHANGE_NOTIFICATION ; 
 int EDD_INFO_NO_MEDIA_PRESENT ; 
 int EDD_INFO_REMOVABLE ; 
 int EDD_INFO_USE_INT13_FN50 ; 
 int EDD_INFO_WRITE_VERIFY ; 
 int EINVAL ; 
 struct edd_info* edd_dev_get_info (struct edd_device*) ; 
 int /*<<< orphan*/  left ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
edd_show_info_flags(struct edd_device *edev, char *buf)
{
	struct edd_info *info;
	char *p = buf;
	if (!edev)
		return -EINVAL;
	info = edd_dev_get_info(edev);
	if (!info || !buf)
		return -EINVAL;

	if (info->params.info_flags & EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT)
		p += scnprintf(p, left, "DMA boundary error transparent\n");
	if (info->params.info_flags & EDD_INFO_GEOMETRY_VALID)
		p += scnprintf(p, left, "geometry valid\n");
	if (info->params.info_flags & EDD_INFO_REMOVABLE)
		p += scnprintf(p, left, "removable\n");
	if (info->params.info_flags & EDD_INFO_WRITE_VERIFY)
		p += scnprintf(p, left, "write verify\n");
	if (info->params.info_flags & EDD_INFO_MEDIA_CHANGE_NOTIFICATION)
		p += scnprintf(p, left, "media change notification\n");
	if (info->params.info_flags & EDD_INFO_LOCKABLE)
		p += scnprintf(p, left, "lockable\n");
	if (info->params.info_flags & EDD_INFO_NO_MEDIA_PRESENT)
		p += scnprintf(p, left, "no media present\n");
	if (info->params.info_flags & EDD_INFO_USE_INT13_FN50)
		p += scnprintf(p, left, "use int13 fn50\n");
	return (p - buf);
}