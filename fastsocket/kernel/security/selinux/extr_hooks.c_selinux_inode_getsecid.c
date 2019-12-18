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
typedef  int /*<<< orphan*/  u32 ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {struct inode_security_struct* i_security; } ;

/* Variables and functions */

__attribute__((used)) static void selinux_inode_getsecid(const struct inode *inode, u32 *secid)
{
	struct inode_security_struct *isec = inode->i_security;
	*secid = isec->sid;
}