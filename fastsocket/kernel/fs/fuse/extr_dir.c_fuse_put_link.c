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
struct nameidata {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_get_link (struct nameidata*) ; 

__attribute__((used)) static void fuse_put_link(struct dentry *dentry, struct nameidata *nd, void *c)
{
	free_link(nd_get_link(nd));
}