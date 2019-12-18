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
struct gcry_mpi {int dummy; } ;
typedef  struct gcry_mpi* MPI ;

/* Variables and functions */

void mpi_swap(MPI a, MPI b)
{
	struct gcry_mpi tmp;

	tmp = *a; *a = *b; *b = tmp;
}