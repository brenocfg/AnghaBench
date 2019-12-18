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
typedef  int u32 ;
struct TYPE_3__ {int iram_addr; int iram_len; int init_vec; scalar_t__ iram_maddr; } ;
typedef  TYPE_1__ dsptask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_CheckMailFrom () ; 
 scalar_t__ DSP_CheckMailTo () ; 
 int DSP_ReadMailFrom () ; 
 int /*<<< orphan*/  DSP_SendMailTo (int) ; 

__attribute__((used)) static void __dsp_boottask(dsptask_t *task)
{
	u32 mail;
	while(!DSP_CheckMailFrom());
	mail = DSP_ReadMailFrom();
	DSP_SendMailTo(0x80F3A001);
	while(DSP_CheckMailTo());
	DSP_SendMailTo((u32)task->iram_maddr);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(0x80F3C002);
	while(DSP_CheckMailTo());
	DSP_SendMailTo((task->iram_addr&0xffff));
	while(DSP_CheckMailTo());
	DSP_SendMailTo(0x80F3A002);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(task->iram_len);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(0x80F3B002);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(0);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(0x80F3D001);
	while(DSP_CheckMailTo());
	DSP_SendMailTo(task->init_vec);
	while(DSP_CheckMailTo());
}