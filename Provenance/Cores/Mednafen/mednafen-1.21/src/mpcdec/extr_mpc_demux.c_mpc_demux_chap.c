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
struct TYPE_4__ {int chap_nb; int /*<<< orphan*/  const* chap; } ;
typedef  TYPE_1__ mpc_demux ;
typedef  int /*<<< orphan*/  mpc_chap_info ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_demux_chap_find (TYPE_1__*) ; 

mpc_chap_info const * mpc_demux_chap(mpc_demux * d, int chap_nb)
{
	if (d->chap_nb == -1)
		mpc_demux_chap_find(d);
	if (chap_nb >= d->chap_nb || chap_nb < 0)
		return 0;
	return &d->chap[chap_nb];
}