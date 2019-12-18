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
struct TYPE_3__ {scalar_t__ flags; scalar_t__ nbits; scalar_t__ nlimbs; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */

void mpi_clear(MPI a)
{
	a->nlimbs = 0;
	a->nbits = 0;
	a->flags = 0;
}