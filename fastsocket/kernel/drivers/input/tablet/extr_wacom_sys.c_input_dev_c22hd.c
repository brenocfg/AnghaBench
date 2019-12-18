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
struct input_dev {int /*<<< orphan*/ * keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_PROG1 ; 
 int /*<<< orphan*/  KEY_PROG2 ; 
 int /*<<< orphan*/  KEY_PROG3 ; 

void input_dev_c22hd(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	input_dev->keybit[BIT_WORD(KEY_PROG1)] |= BIT_MASK(KEY_PROG1);
	input_dev->keybit[BIT_WORD(KEY_PROG2)] |= BIT_MASK(KEY_PROG2);
	input_dev->keybit[BIT_WORD(KEY_PROG3)] |= BIT_MASK(KEY_PROG3);
}