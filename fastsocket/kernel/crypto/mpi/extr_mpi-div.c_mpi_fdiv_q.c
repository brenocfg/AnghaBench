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
 int /*<<< orphan*/  mpi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_fdiv_qr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_get_nlimbs (int /*<<< orphan*/ ) ; 

int
mpi_fdiv_q( MPI quot, MPI dividend, MPI divisor )
{
    MPI tmp = mpi_alloc( mpi_get_nlimbs(quot) );
    if (!tmp)
	    return -ENOMEM;
    mpi_fdiv_qr( quot, tmp, dividend, divisor);
    mpi_free(tmp);
    return 0;
}