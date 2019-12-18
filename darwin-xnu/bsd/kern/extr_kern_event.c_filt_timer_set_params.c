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
struct knote {int /*<<< orphan*/  kn_sdata; int /*<<< orphan*/ * kn_ext; } ;
struct filt_timer_params {int /*<<< orphan*/  interval; int /*<<< orphan*/  leeway; int /*<<< orphan*/  deadline; } ;

/* Variables and functions */

__attribute__((used)) static void
filt_timer_set_params(struct knote *kn, struct filt_timer_params *params)
{
	kn->kn_ext[0] = params->deadline;
	kn->kn_ext[1] = params->leeway;
	kn->kn_sdata  = params->interval;
}