#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_status ;
typedef  int /*<<< orphan*/  mpc_int64_t ;
struct TYPE_5__ {scalar_t__ sample_freq; } ;
struct TYPE_6__ {TYPE_1__ si; } ;
typedef  TYPE_2__ mpc_demux ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_demux_seek_sample (TYPE_2__*,int /*<<< orphan*/ ) ; 

mpc_status mpc_demux_seek_second(mpc_demux * d, double seconds)
{
	return mpc_demux_seek_sample(d, (mpc_int64_t)(seconds * (double)d->si.sample_freq + 0.5));
}