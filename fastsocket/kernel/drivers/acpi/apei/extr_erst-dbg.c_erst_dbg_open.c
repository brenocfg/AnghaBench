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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ erst_disable ; 
 int erst_get_record_id_begin (int*) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int erst_dbg_open(struct inode *inode, struct file *file)
{
	int rc, *pos;

	if (erst_disable)
		return -ENODEV;

	pos = (int *)&file->private_data;

	rc = erst_get_record_id_begin(pos);
	if (rc)
		return rc;

	return nonseekable_open(inode, file);
}