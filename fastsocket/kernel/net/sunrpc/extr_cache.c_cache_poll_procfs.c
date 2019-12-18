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
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_6__ {struct cache_detail* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 TYPE_3__* PDE (int /*<<< orphan*/ ) ; 
 unsigned int cache_poll (struct file*,int /*<<< orphan*/ *,struct cache_detail*) ; 

__attribute__((used)) static unsigned int cache_poll_procfs(struct file *filp, poll_table *wait)
{
	struct cache_detail *cd = PDE(filp->f_path.dentry->d_inode)->data;

	return cache_poll(filp, wait, cd);
}