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
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  exofs_file_fsync (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exofs_flush(struct file *file, fl_owner_t id)
{
	exofs_file_fsync(file, file->f_path.dentry, 1);
	/* TODO: Flush the OSD target */
	return 0;
}