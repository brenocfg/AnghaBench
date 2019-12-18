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
 scalar_t__ mpi_test_bit (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static int
build_index(const MPI *exparray, int k, int i, int t )
{
    int j, bitno;
    int index = 0;

    bitno = t-i;
    for(j=k-1; j >= 0; j-- ) {
	index <<= 1;
	if( mpi_test_bit( exparray[j], bitno ) )
	    index |= 1;
    }
    return index;
}