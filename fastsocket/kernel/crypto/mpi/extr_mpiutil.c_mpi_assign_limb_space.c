#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpi_ptr_t ;
struct TYPE_3__ {unsigned int alloced; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int /*<<< orphan*/  mpi_free_limb_space (int /*<<< orphan*/ ) ; 

void mpi_assign_limb_space(MPI a, mpi_ptr_t ap, unsigned nlimbs)
{
    mpi_free_limb_space(a->d);
    a->d = ap;
    a->alloced = nlimbs;
}