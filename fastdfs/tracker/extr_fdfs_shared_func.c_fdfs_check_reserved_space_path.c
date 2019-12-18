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
typedef  int int64_t ;
struct TYPE_4__ {double ratio; } ;
struct TYPE_5__ {scalar_t__ flag; TYPE_1__ rs; } ;
typedef  TYPE_2__ FDFSStorageReservedSpace ;

/* Variables and functions */
 scalar_t__ TRACKER_STORAGE_RESERVED_SPACE_FLAG_MB ; 

bool fdfs_check_reserved_space_path(const int64_t total_mb, \
	const int64_t free_mb, const int avg_mb, \
	FDFSStorageReservedSpace *pStorageReservedSpace)
{
	if (pStorageReservedSpace->flag == \
			TRACKER_STORAGE_RESERVED_SPACE_FLAG_MB)
	{
		return free_mb > avg_mb;
	}
	else
	{
		if (total_mb == 0)
		{
			return false;
		}

		/*
		logInfo("storage path, free_mb=%"PRId64 \
			", total_mb=%"PRId64", " \
			"real ratio=%.4f, rs.ratio=%.4f", \
			free_mb, total_mb, ((double)free_mb / total_mb), \
			pStorageReservedSpace->rs.ratio);
		*/

		return ((double)free_mb / (double)total_mb) > \
			pStorageReservedSpace->rs.ratio;
	}
}