#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ prof_interval; } ;
typedef  TYPE_1__ profile_probe_t ;
struct TYPE_8__ {scalar_t__ profc_interval; scalar_t__ profc_expected; TYPE_1__* profc_probe; } ;
typedef  TYPE_2__ profile_probe_percpu_t ;
typedef  int /*<<< orphan*/  dtrace_cpu_t ;
struct TYPE_9__ {scalar_t__ cyt_interval; scalar_t__ cyt_when; } ;
typedef  TYPE_3__ cyc_time_t ;
struct TYPE_10__ {int /*<<< orphan*/  cyh_level; TYPE_2__* cyh_arg; int /*<<< orphan*/  cyh_func; } ;
typedef  TYPE_4__ cyc_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  CY_HIGH_LEVEL ; 
 int cpu_number () ; 
 scalar_t__ dtrace_gethrtime () ; 
 int /*<<< orphan*/  profile_fire ; 

__attribute__((used)) static void
profile_online(void *arg, dtrace_cpu_t *cpu, cyc_handler_t *hdlr, cyc_time_t *when)
{
#pragma unused(cpu) /* __APPLE__ */
	profile_probe_t *prof = arg;
	profile_probe_percpu_t *pcpu;

	pcpu = ((profile_probe_percpu_t *)(&(prof[1]))) + cpu_number();
	pcpu->profc_probe = prof;

	hdlr->cyh_func = profile_fire;
	hdlr->cyh_arg = pcpu;
	hdlr->cyh_level = CY_HIGH_LEVEL;

	when->cyt_interval = prof->prof_interval;
	when->cyt_when = dtrace_gethrtime() + when->cyt_interval;

	pcpu->profc_expected = when->cyt_when;
	pcpu->profc_interval = when->cyt_interval;
}