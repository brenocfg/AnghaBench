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
typedef  int mpc_int_t ;
struct TYPE_4__ {int chap_nb; } ;
typedef  TYPE_1__ mpc_demux ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_demux_chap_find (TYPE_1__*) ; 

mpc_int_t mpc_demux_chap_nb(mpc_demux * d)
{
	if (d->chap_nb == -1)
		mpc_demux_chap_find(d);
	return d->chap_nb;
}