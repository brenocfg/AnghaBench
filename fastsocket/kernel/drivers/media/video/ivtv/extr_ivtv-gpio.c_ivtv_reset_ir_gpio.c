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
struct ivtv {TYPE_1__* card; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ IVTV_CARD_PVR_150 ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_REG_GPIO_DIR ; 
 int /*<<< orphan*/  IVTV_REG_GPIO_OUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

void ivtv_reset_ir_gpio(struct ivtv *itv)
{
	int curdir, curout;

	if (itv->card->type != IVTV_CARD_PVR_150)
		return;
	IVTV_DEBUG_INFO("Resetting PVR150 IR\n");
	curout = read_reg(IVTV_REG_GPIO_OUT);
	curdir = read_reg(IVTV_REG_GPIO_DIR);
	curdir |= 0x80;
	write_reg(curdir, IVTV_REG_GPIO_DIR);
	curout = (curout & ~0xF) | 1;
	write_reg(curout, IVTV_REG_GPIO_OUT);
	/* We could use something else for smaller time */
	schedule_timeout_interruptible(msecs_to_jiffies(1));
	curout |= 2;
	write_reg(curout, IVTV_REG_GPIO_OUT);
	curdir &= ~0x80;
	write_reg(curdir, IVTV_REG_GPIO_DIR);
}