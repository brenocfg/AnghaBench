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
struct ipath_filedata {int dummy; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipath_open(struct inode *in, struct file *fp)
{
	/* The real work is performed later in ipath_assign_port() */
	fp->private_data = kzalloc(sizeof(struct ipath_filedata), GFP_KERNEL);
	return fp->private_data ? 0 : -ENOMEM;
}