#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* data; } ;
struct irctl {TYPE_1__ d; } ;
struct file {TYPE_2__* f_dentry; } ;
struct TYPE_6__ {scalar_t__ i_rdev; } ;
struct TYPE_5__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 size_t iminor (TYPE_3__*) ; 
 struct irctl** irctls ; 

void *lirc_get_pdata(struct file *file)
{
	void *data = NULL;

	if (file && file->f_dentry && file->f_dentry->d_inode &&
	    file->f_dentry->d_inode->i_rdev) {
		struct irctl *ir;
		ir = irctls[iminor(file->f_dentry->d_inode)];
		data = ir->d.data;
	}

	return data;
}