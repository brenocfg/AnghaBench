#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {unsigned short joy0dat; unsigned short potgor; } ;
struct TYPE_3__ {int pra; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 TYPE_2__ amiga_custom ; 
 int /*<<< orphan*/  amimouse_dev ; 
 int amimouse_lastx ; 
 int amimouse_lasty ; 
 TYPE_1__ ciaa ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t amimouse_interrupt(int irq, void *dummy)
{
	unsigned short joy0dat, potgor;
	int nx, ny, dx, dy;

	joy0dat = amiga_custom.joy0dat;

	nx = joy0dat & 0xff;
	ny = joy0dat >> 8;

	dx = nx - amimouse_lastx;
	dy = ny - amimouse_lasty;

	if (dx < -127) dx = (256 + nx) - amimouse_lastx;
	if (dx >  127) dx = (nx - 256) - amimouse_lastx;
	if (dy < -127) dy = (256 + ny) - amimouse_lasty;
	if (dy >  127) dy = (ny - 256) - amimouse_lasty;

	amimouse_lastx = nx;
	amimouse_lasty = ny;

	potgor = amiga_custom.potgor;

	input_report_rel(amimouse_dev, REL_X, dx);
	input_report_rel(amimouse_dev, REL_Y, dy);

	input_report_key(amimouse_dev, BTN_LEFT,   ciaa.pra & 0x40);
	input_report_key(amimouse_dev, BTN_MIDDLE, potgor & 0x0100);
	input_report_key(amimouse_dev, BTN_RIGHT,  potgor & 0x0400);

	input_sync(amimouse_dev);

	return IRQ_HANDLED;
}