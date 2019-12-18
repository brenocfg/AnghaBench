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
struct TYPE_4__ {double mb; double ratio; } ;
struct TYPE_5__ {scalar_t__ flag; TYPE_1__ rs; } ;
typedef  TYPE_2__ FDFSStorageReservedSpace ;

/* Variables and functions */
 scalar_t__ TRACKER_STORAGE_RESERVED_SPACE_FLAG_MB ; 
 int /*<<< orphan*/  sprintf (char*,char*,double) ; 

const char *fdfs_storage_reserved_space_to_string(FDFSStorageReservedSpace \
			*pStorageReservedSpace, char *buff)
{
	if (pStorageReservedSpace->flag == \
			TRACKER_STORAGE_RESERVED_SPACE_FLAG_MB)
	{
		sprintf(buff, "%d MB", pStorageReservedSpace->rs.mb);
	}
	else
	{
		sprintf(buff, "%.2f%%", 100.00 * \
			pStorageReservedSpace->rs.ratio);
	}

	return buff;
}