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
struct ncp_mount_data_v4 {int /*<<< orphan*/  flags; int /*<<< orphan*/  mounted_uid; int /*<<< orphan*/  wdog_pid; int /*<<< orphan*/  ncp_fd; int /*<<< orphan*/  time_out; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  dir_mode; } ;
struct ncp_mount_data {int /*<<< orphan*/  mounted_uid; int /*<<< orphan*/  wdog_pid; int /*<<< orphan*/  mounted_vol; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  dir_mode; } ;
struct compat_ncp_mount_data_v4 {int /*<<< orphan*/  flags; int /*<<< orphan*/  mounted_uid; int /*<<< orphan*/  wdog_pid; int /*<<< orphan*/  ncp_fd; int /*<<< orphan*/  time_out; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  dir_mode; } ;
struct compat_ncp_mount_data {int /*<<< orphan*/  mounted_uid; int /*<<< orphan*/  wdog_pid; int /*<<< orphan*/  mounted_vol; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  dir_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *do_ncp_super_data_conv(void *raw_data)
{
	int version = *(unsigned int *)raw_data;

	if (version == 3) {
		struct compat_ncp_mount_data *c_n = raw_data;
		struct ncp_mount_data *n = raw_data;

		n->dir_mode = c_n->dir_mode;
		n->file_mode = c_n->file_mode;
		n->gid = c_n->gid;
		n->uid = c_n->uid;
		memmove (n->mounted_vol, c_n->mounted_vol, (sizeof (c_n->mounted_vol) + 3 * sizeof (unsigned int)));
		n->wdog_pid = c_n->wdog_pid;
		n->mounted_uid = c_n->mounted_uid;
	} else if (version == 4) {
		struct compat_ncp_mount_data_v4 *c_n = raw_data;
		struct ncp_mount_data_v4 *n = raw_data;

		n->dir_mode = c_n->dir_mode;
		n->file_mode = c_n->file_mode;
		n->gid = c_n->gid;
		n->uid = c_n->uid;
		n->retry_count = c_n->retry_count;
		n->time_out = c_n->time_out;
		n->ncp_fd = c_n->ncp_fd;
		n->wdog_pid = c_n->wdog_pid;
		n->mounted_uid = c_n->mounted_uid;
		n->flags = c_n->flags;
	} else if (version != 5) {
		return NULL;
	}

	return raw_data;
}