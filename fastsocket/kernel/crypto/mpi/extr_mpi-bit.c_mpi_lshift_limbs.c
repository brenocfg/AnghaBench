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
typedef  scalar_t__* mpi_ptr_t ;
struct TYPE_4__ {int nlimbs; scalar_t__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ RESIZE_IF_NEEDED (TYPE_1__*,int) ; 

int
mpi_lshift_limbs( MPI a, unsigned int count )
{
    mpi_ptr_t ap = a->d;
    int n = a->nlimbs;
    int i;

    if( !count || !n )
	return 0;

    if (RESIZE_IF_NEEDED( a, n+count ) < 0) return -ENOMEM;

    for( i = n-1; i >= 0; i-- )
	ap[i+count] = ap[i];
    for(i=0; i < count; i++ )
	ap[i] = 0;
    a->nlimbs += count;
    return 0;
}