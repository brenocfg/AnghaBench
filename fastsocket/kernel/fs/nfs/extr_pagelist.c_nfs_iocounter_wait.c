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
struct nfs_io_counter {int /*<<< orphan*/  io_count; } ;

/* Variables and functions */
 int __nfs_iocounter_wait (struct nfs_io_counter*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

int
nfs_iocounter_wait(struct nfs_io_counter *c)
{
	if (atomic_read(&c->io_count) == 0)
		return 0;
	return __nfs_iocounter_wait(c);
}