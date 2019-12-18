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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  dram_addr; int /*<<< orphan*/  dram_len; scalar_t__ dram_maddr; int /*<<< orphan*/  resume_vec; int /*<<< orphan*/  init_vec; int /*<<< orphan*/  iram_addr; int /*<<< orphan*/  iram_len; scalar_t__ iram_maddr; } ;
typedef  TYPE_1__ dsptask_t ;

/* Variables and functions */
 scalar_t__ DSPTASK_INIT ; 
 scalar_t__ DSP_CheckMailTo () ; 
 int /*<<< orphan*/  DSP_SendMailTo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dsp_exectask(dsptask_t *exec,dsptask_t *hire)
{
	if(!exec) {
		DSP_SendMailTo(0);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(0);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(0);
		while(DSP_CheckMailTo());
	} else {
		DSP_SendMailTo((u32)exec->dram_maddr);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(exec->dram_len);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(exec->dram_addr);
		while(DSP_CheckMailTo());
	}

	DSP_SendMailTo((u32)hire->iram_maddr);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(hire->iram_len);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(hire->iram_addr);
	while(DSP_CheckMailTo());
	if(hire->state==DSPTASK_INIT) {
		DSP_SendMailTo(hire->init_vec);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(0);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(0);
		while(DSP_CheckMailTo());
		DSP_SendMailTo(0);
		while(DSP_CheckMailTo());
		return;
	}

	DSP_SendMailTo(hire->resume_vec);
	while(DSP_CheckMailTo());

	DSP_SendMailTo((u32)hire->dram_maddr);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(hire->dram_len);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(hire->dram_addr);
	while(DSP_CheckMailTo());
}