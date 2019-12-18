#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_2__* f_dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CHECK ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  ima_enabled ; 
 int process_measurement (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ima_file_check(struct file *file, int mask)
{
	int rc;

	if (!ima_enabled)
		return 0;

	rc = process_measurement(file, file->f_dentry->d_name.name,
				 mask & (MAY_READ | MAY_WRITE | MAY_EXEC),
				 FILE_CHECK);
	return 0;
}