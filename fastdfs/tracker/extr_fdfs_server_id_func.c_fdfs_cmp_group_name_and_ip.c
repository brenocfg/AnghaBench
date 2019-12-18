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
struct TYPE_2__ {int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  group_name; } ;
typedef  TYPE_1__ FDFSStorageIdMap ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdfs_cmp_group_name_and_ip(const void *p1, const void *p2)
{
	int result;
	result = strcmp(((FDFSStorageIdMap *)p1)->group_name,
		((FDFSStorageIdMap *)p2)->group_name);
	if (result != 0)
	{
		return result;
	}

	return strcmp(((FDFSStorageIdMap *)p1)->ip_addr,
		((FDFSStorageIdMap *)p2)->ip_addr);
}