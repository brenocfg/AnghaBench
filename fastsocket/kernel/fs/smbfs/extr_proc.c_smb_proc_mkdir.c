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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBmkdir ; 
 int smb_proc_generic_command (struct dentry*,int /*<<< orphan*/ ) ; 

int
smb_proc_mkdir(struct dentry *dentry)
{
	return smb_proc_generic_command(dentry, SMBmkdir);
}