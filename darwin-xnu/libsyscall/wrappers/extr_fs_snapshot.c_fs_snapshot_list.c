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
typedef  scalar_t__ uint32_t ;
struct attrlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FSOPT_LIST_SNAPSHOT ; 
 int /*<<< orphan*/  errno ; 
 int getattrlistbulk (int,struct attrlist*,void*,size_t,int /*<<< orphan*/ ) ; 

int
fs_snapshot_list(int dirfd, struct attrlist *alist, void *attrbuf, size_t bufsize,
    uint32_t flags)
{
	if (flags != 0) {
		errno = EINVAL;
		return (-1);
	}

	return (getattrlistbulk(dirfd, alist, attrbuf, bufsize,
	    FSOPT_LIST_SNAPSHOT));
}