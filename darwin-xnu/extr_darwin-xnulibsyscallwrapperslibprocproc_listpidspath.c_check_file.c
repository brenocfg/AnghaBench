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
struct vinfo_stat {scalar_t__ vst_dev; scalar_t__ vst_ino; } ;
typedef  TYPE_2__* fdOpenInfoRef ;
struct TYPE_4__ {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct TYPE_5__ {int flags; TYPE_1__ match_stat; } ;

/* Variables and functions */
 int PROC_LISTPIDSPATH_PATH_IS_VOLUME ; 

__attribute__((used)) static int
check_file(fdOpenInfoRef info, struct vinfo_stat *sb)
{
	if (sb->vst_dev == 0) {
		// if no info
		return 0;
	}

	if (sb->vst_dev != info->match_stat.st_dev) {
		// if not the requested filesystem
		return 0;
	}

	if (!(info->flags & PROC_LISTPIDSPATH_PATH_IS_VOLUME) &&
	    (sb->vst_ino != info->match_stat.st_ino)) {
		// if not the requested file
		return 0;
	}

	return 1;
}