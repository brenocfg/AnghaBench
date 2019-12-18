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
typedef  scalar_t__ mpi_limb_t ;
struct TYPE_4__ {int nlimbs; scalar_t__* d; scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int /*<<< orphan*/  mpi_normalize (TYPE_1__*) ; 

int
mpi_cmp_ui( MPI u, unsigned long v )
{
    mpi_limb_t limb = v;

    mpi_normalize( u );
    if( !u->nlimbs && !limb )
	return 0;
    if( u->sign )
	return -1;
    if( u->nlimbs > 1 )
	return 1;

    if( u->d[0] == limb )
	return 0;
    else if( u->d[0] > limb )
	return 1;
    else
	return -1;
}