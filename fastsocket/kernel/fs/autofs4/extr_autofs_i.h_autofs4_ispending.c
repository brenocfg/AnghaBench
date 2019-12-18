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
struct autofs_info {int flags; } ;

/* Variables and functions */
 int AUTOFS_INF_EXPIRING ; 
 int AUTOFS_INF_PENDING ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 

__attribute__((used)) static inline int autofs4_ispending(struct dentry *dentry)
{
	struct autofs_info *inf = autofs4_dentry_ino(dentry);

	if (inf->flags & AUTOFS_INF_PENDING)
		return 1;

	if (inf->flags & AUTOFS_INF_EXPIRING)
		return 1;

	return 0;
}