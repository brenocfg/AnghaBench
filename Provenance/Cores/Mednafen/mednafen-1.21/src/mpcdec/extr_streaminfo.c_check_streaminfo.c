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
struct TYPE_3__ {int max_band; int channels; scalar_t__ sample_freq; } ;
typedef  TYPE_1__ mpc_streaminfo ;
typedef  int /*<<< orphan*/  mpc_status ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_STATUS_FAIL ; 
 int /*<<< orphan*/  MPC_STATUS_OK ; 

__attribute__((used)) static mpc_status check_streaminfo(mpc_streaminfo * si)
{
	if (si->max_band == 0 || si->max_band >= 32
	    || si->channels > 2 || si->channels == 0 || si->sample_freq == 0)
		return MPC_STATUS_FAIL;
	return MPC_STATUS_OK;
}