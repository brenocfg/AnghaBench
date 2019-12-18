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
struct smb_mount_data {int /*<<< orphan*/  mounted_uid; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  dir_mode; } ;
struct compat_smb_mount_data {scalar_t__ version; int /*<<< orphan*/  mounted_uid; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  dir_mode; } ;

/* Variables and functions */
 scalar_t__ SMB_MOUNT_OLDVERSION ; 

__attribute__((used)) static void *do_smb_super_data_conv(void *raw_data)
{
	struct smb_mount_data *s = raw_data;
	struct compat_smb_mount_data *c_s = raw_data;

	if (c_s->version != SMB_MOUNT_OLDVERSION)
		goto out;
	s->dir_mode = c_s->dir_mode;
	s->file_mode = c_s->file_mode;
	s->gid = c_s->gid;
	s->uid = c_s->uid;
	s->mounted_uid = c_s->mounted_uid;
 out:
	return raw_data;
}