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
typedef  int* mpi_ptr_t ;
typedef  int mpi_limb_t ;
struct TYPE_3__ {int* d; int nlimbs; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int BYTES_PER_MPI_LIMB ; 

int
mpi_getbyte( const MPI a, unsigned idx )
{
    int i, j;
    unsigned n;
    mpi_ptr_t ap;
    mpi_limb_t limb;

    ap = a->d;
    for(n=0,i=0; i < a->nlimbs; i++ ) {
	limb = ap[i];
	for( j=0; j < BYTES_PER_MPI_LIMB; j++, n++ )
	    if( n == idx )
		return (limb >> j*8) & 0xff;
    }
    return -1;
}