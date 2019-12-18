#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zinject_record_t ;
struct TYPE_3__ {scalar_t__ zc_guid; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_CLEAR_FAULT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_fd ; 

__attribute__((used)) static int
cancel_one_handler(int id, const char *pool, zinject_record_t *record,
    void *data)
{
	zfs_cmd_t zc = { 0 };

	zc.zc_guid = (uint64_t)id;

	if (ioctl(zfs_fd, ZFS_IOC_CLEAR_FAULT, &zc) != 0) {
		(void) fprintf(stderr, "failed to remove handler %d: %s\n",
		    id, strerror(errno));
		return (1);
	}

	return (0);
}