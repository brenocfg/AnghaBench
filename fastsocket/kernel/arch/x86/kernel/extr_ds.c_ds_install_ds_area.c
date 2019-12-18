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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ds_context {scalar_t__ task; int /*<<< orphan*/  cpu; scalar_t__ ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_DS_AREA ; 
 int /*<<< orphan*/  TIF_DS_AREA_MSR ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  set_tsk_thread_flag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ds_install_ds_area(struct ds_context *context)
{
	unsigned long ds;

	ds = (unsigned long)context->ds;

	/*
	 * There is a race between the bts master and the pebs master.
	 *
	 * The thread/cpu access is synchronized via get/put_cpu() for
	 * task tracing and via wrmsr_on_cpu for cpu tracing.
	 *
	 * If bts and pebs are collected for the same task or same cpu,
	 * the same confiuration is written twice.
	 */
	if (context->task) {
		get_cpu();
		if (context->task == current)
			wrmsrl(MSR_IA32_DS_AREA, ds);
		set_tsk_thread_flag(context->task, TIF_DS_AREA_MSR);
		put_cpu();
	} else
		wrmsr_on_cpu(context->cpu, MSR_IA32_DS_AREA,
			     (u32)((u64)ds), (u32)((u64)ds >> 32));
}