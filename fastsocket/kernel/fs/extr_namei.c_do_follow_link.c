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
struct path {int /*<<< orphan*/  dentry; } ;
struct nameidata {scalar_t__ depth; int /*<<< orphan*/  path; } ;
struct TYPE_2__ {scalar_t__ link_count; int total_link_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ELOOP ; 
 scalar_t__ MAX_NESTED_LINKS ; 
 int __do_follow_link (struct path*,struct nameidata*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put_conditional (struct path*,struct nameidata*) ; 
 int security_inode_follow_link (int /*<<< orphan*/ ,struct nameidata*) ; 

__attribute__((used)) static inline int do_follow_link(struct path *path, struct nameidata *nd)
{
	int err = -ELOOP;
	if (current->link_count >= MAX_NESTED_LINKS)
		goto loop;
	if (current->total_link_count >= 40)
		goto loop;
	BUG_ON(nd->depth >= MAX_NESTED_LINKS);
	cond_resched();
	err = security_inode_follow_link(path->dentry, nd);
	if (err)
		goto loop;
	current->link_count++;
	current->total_link_count++;
	nd->depth++;
	err = __do_follow_link(path, nd);
	current->link_count--;
	nd->depth--;
	return err;
loop:
	path_put_conditional(path, nd);
	path_put(&nd->path);
	return err;
}