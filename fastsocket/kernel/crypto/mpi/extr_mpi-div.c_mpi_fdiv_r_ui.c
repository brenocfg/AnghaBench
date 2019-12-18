#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  scalar_t__ mpi_limb_t ;
struct TYPE_4__ {int nlimbs; scalar_t__* d; scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 scalar_t__ mpihelp_mod_1 (scalar_t__*,int,scalar_t__) ; 

ulong
mpi_fdiv_r_ui( MPI rem, MPI dividend, ulong divisor )
{
    mpi_limb_t rlimb;

    rlimb = mpihelp_mod_1( dividend->d, dividend->nlimbs, divisor );
    if( rlimb && dividend->sign )
	rlimb = divisor - rlimb;

    if( rem ) {
	rem->d[0] = rlimb;
	rem->nlimbs = rlimb? 1:0;
    }
    return rlimb;
}