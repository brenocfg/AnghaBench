#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ free_mb; scalar_t__ total_mb; } ;
struct TYPE_6__ {scalar_t__ mb; double ratio; } ;
struct TYPE_7__ {scalar_t__ flag; TYPE_1__ rs; } ;
typedef  TYPE_2__ FDFSStorageReservedSpace ;
typedef  TYPE_3__ FDFSGroupInfo ;

/* Variables and functions */
 scalar_t__ TRACKER_STORAGE_RESERVED_SPACE_FLAG_MB ; 

bool fdfs_check_reserved_space(FDFSGroupInfo *pGroup, \
	FDFSStorageReservedSpace *pStorageReservedSpace)
{
	if (pStorageReservedSpace->flag == \
			TRACKER_STORAGE_RESERVED_SPACE_FLAG_MB)
	{
		return pGroup->free_mb > pStorageReservedSpace->rs.mb;
	}
	else
	{
		if (pGroup->total_mb == 0)
		{
			return false;
		}

		/*
		logInfo("storage=%.4f, rs.ratio=%.4f", 
			((double)pGroup->free_mb / (double)pGroup->total_mb),
			pStorageReservedSpace->rs.ratio);
		*/

		return ((double)pGroup->free_mb / (double)pGroup->total_mb) > \
			pStorageReservedSpace->rs.ratio;
	}
}