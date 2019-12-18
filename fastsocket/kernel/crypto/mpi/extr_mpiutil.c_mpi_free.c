#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; struct TYPE_5__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mpi_free_limb_space (TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*) ; 

void mpi_free(MPI a)
{
	if (!a)
		return;

	if (a->flags & 4)
		kfree(a->d);
	else {
		mpi_free_limb_space(a->d);
	}

	if (a->flags & ~7 )
		printk("invalid flag value in mpi\n");
	kfree(a);
}