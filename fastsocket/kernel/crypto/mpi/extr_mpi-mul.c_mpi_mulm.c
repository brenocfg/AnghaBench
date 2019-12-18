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
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 int ENOMEM ; 
 int mpi_fdiv_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mpi_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mpi_mulm( MPI w, MPI u, MPI v, MPI m)
{
	if (mpi_mul(w, u, v) < 0)
		return -ENOMEM;
	return mpi_fdiv_r( w, w, m );
}