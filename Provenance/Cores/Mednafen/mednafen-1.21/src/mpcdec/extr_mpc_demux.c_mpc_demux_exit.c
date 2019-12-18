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
struct TYPE_4__ {struct TYPE_4__* chap; struct TYPE_4__* seek_table; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ mpc_demux ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_decoder_exit (int /*<<< orphan*/ ) ; 

void mpc_demux_exit(mpc_demux * d)
{
	mpc_decoder_exit(d->d);
	free(d->seek_table);
	free(d->chap);
	free(d);
}