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
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mnt_drop_write (int /*<<< orphan*/ ) ; 

void __mnt_drop_write_file(struct file *file)
{
	__mnt_drop_write(file->f_path.mnt);
}