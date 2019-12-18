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
struct fnode {int ea_offs; int acl_size_s; int ea_size_s; } ;
struct extended_attribute {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct extended_attribute *fnode_end_ea(struct fnode *fnode)
{
	return (struct extended_attribute *)((char *)fnode + fnode->ea_offs + fnode->acl_size_s + fnode->ea_size_s);
}