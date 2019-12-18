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
struct wacom_wac {int dummy; } ;
struct input_dev {int* evbit; int* mscbit; int* keybit; } ;

/* Variables and functions */
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_4 ; 
 int /*<<< orphan*/  BTN_DIGI ; 
 int /*<<< orphan*/  BTN_MISC ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 

void input_dev_g4(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	input_dev->evbit[0] |= BIT_MASK(EV_MSC);
	input_dev->mscbit[0] |= BIT_MASK(MSC_SERIAL);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |= BIT_MASK(BTN_TOOL_FINGER);
	input_dev->keybit[BIT_WORD(BTN_MISC)] |= BIT_MASK(BTN_0) |
		BIT_MASK(BTN_4);
}