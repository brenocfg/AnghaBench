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
struct file {int f_mode; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int FMODE_READ ; 
 int /*<<< orphan*/  seq_lseek (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static loff_t tracing_seek(struct file *file, loff_t offset, int origin)
{
	if (file->f_mode & FMODE_READ)
		return seq_lseek(file, offset, origin);
	else
		return 0;
}