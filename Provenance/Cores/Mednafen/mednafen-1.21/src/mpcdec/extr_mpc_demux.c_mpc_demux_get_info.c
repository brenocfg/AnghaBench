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
typedef  int /*<<< orphan*/  mpc_streaminfo ;
struct TYPE_3__ {int /*<<< orphan*/  si; } ;
typedef  TYPE_1__ mpc_demux ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void mpc_demux_get_info(mpc_demux * d, mpc_streaminfo * i)
{
	memcpy(i, &d->si, sizeof d->si);
}