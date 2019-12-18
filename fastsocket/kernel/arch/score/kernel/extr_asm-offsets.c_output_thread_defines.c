#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  trap_no; int /*<<< orphan*/  error_code; int /*<<< orphan*/  cp0_baduaddr; int /*<<< orphan*/  cp0_ema; int /*<<< orphan*/  cp0_psr; int /*<<< orphan*/  reg29; int /*<<< orphan*/  reg21; int /*<<< orphan*/  reg20; int /*<<< orphan*/  reg19; int /*<<< orphan*/  reg18; int /*<<< orphan*/  reg17; int /*<<< orphan*/  reg16; int /*<<< orphan*/  reg15; int /*<<< orphan*/  reg14; int /*<<< orphan*/  reg13; int /*<<< orphan*/  reg12; int /*<<< orphan*/  reg3; int /*<<< orphan*/  reg2; int /*<<< orphan*/  reg0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_BADUADDR ; 
 int /*<<< orphan*/  THREAD_ECODE ; 
 int /*<<< orphan*/  THREAD_EMA ; 
 int /*<<< orphan*/  THREAD_PSR ; 
 int /*<<< orphan*/  THREAD_REG0 ; 
 int /*<<< orphan*/  THREAD_REG12 ; 
 int /*<<< orphan*/  THREAD_REG13 ; 
 int /*<<< orphan*/  THREAD_REG14 ; 
 int /*<<< orphan*/  THREAD_REG15 ; 
 int /*<<< orphan*/  THREAD_REG16 ; 
 int /*<<< orphan*/  THREAD_REG17 ; 
 int /*<<< orphan*/  THREAD_REG18 ; 
 int /*<<< orphan*/  THREAD_REG19 ; 
 int /*<<< orphan*/  THREAD_REG2 ; 
 int /*<<< orphan*/  THREAD_REG20 ; 
 int /*<<< orphan*/  THREAD_REG21 ; 
 int /*<<< orphan*/  THREAD_REG29 ; 
 int /*<<< orphan*/  THREAD_REG3 ; 
 int /*<<< orphan*/  THREAD_TRAPNO ; 
 int /*<<< orphan*/  task_struct ; 
 TYPE_1__ thread ; 

void output_thread_defines(void)
{
	COMMENT("SCORE specific thread_struct offsets.");
	OFFSET(THREAD_REG0, task_struct, thread.reg0);
	OFFSET(THREAD_REG2, task_struct, thread.reg2);
	OFFSET(THREAD_REG3, task_struct, thread.reg3);
	OFFSET(THREAD_REG12, task_struct, thread.reg12);
	OFFSET(THREAD_REG13, task_struct, thread.reg13);
	OFFSET(THREAD_REG14, task_struct, thread.reg14);
	OFFSET(THREAD_REG15, task_struct, thread.reg15);
	OFFSET(THREAD_REG16, task_struct, thread.reg16);
	OFFSET(THREAD_REG17, task_struct, thread.reg17);
	OFFSET(THREAD_REG18, task_struct, thread.reg18);
	OFFSET(THREAD_REG19, task_struct, thread.reg19);
	OFFSET(THREAD_REG20, task_struct, thread.reg20);
	OFFSET(THREAD_REG21, task_struct, thread.reg21);
	OFFSET(THREAD_REG29, task_struct, thread.reg29);

	OFFSET(THREAD_PSR, task_struct, thread.cp0_psr);
	OFFSET(THREAD_EMA, task_struct, thread.cp0_ema);
	OFFSET(THREAD_BADUADDR, task_struct, thread.cp0_baduaddr);
	OFFSET(THREAD_ECODE, task_struct, thread.error_code);
	OFFSET(THREAD_TRAPNO, task_struct, thread.trap_no);
	BLANK();
}