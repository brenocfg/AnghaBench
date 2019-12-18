#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t nlimbs; int /*<<< orphan*/ * d; int /*<<< orphan*/  nbits; int /*<<< orphan*/  flags; int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* MPI_NULL ; 
 TYPE_1__* mpi_alloc (size_t) ; 

int mpi_copy(MPI *copied, const MPI a )
{
	size_t i;
	MPI b;

	*copied = MPI_NULL;

	if ( a ) {
		b = mpi_alloc( a->nlimbs );
		if (!b)
			return -ENOMEM;

		b->nlimbs = a->nlimbs;
		b->sign = a->sign;
		b->flags  = a->flags;
		b->nbits = a->nbits;

		for (i = 0; i < b->nlimbs; i++ )
			b->d[i] = a->d[i];

		*copied = b;
	}

	return 0;
}