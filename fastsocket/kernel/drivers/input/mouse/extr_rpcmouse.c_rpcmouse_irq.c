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
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  IOMD_MOUSEX ; 
 int /*<<< orphan*/  IOMD_MOUSEY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int __raw_readl (int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ iomd_readl (int /*<<< orphan*/ ) ; 
 short rpcmouse_lastx ; 
 short rpcmouse_lasty ; 

__attribute__((used)) static irqreturn_t rpcmouse_irq(int irq, void *dev_id)
{
	struct input_dev *dev = dev_id;
	short x, y, dx, dy, b;

	x = (short) iomd_readl(IOMD_MOUSEX);
	y = (short) iomd_readl(IOMD_MOUSEY);
	b = (short) (__raw_readl(0xe0310000) ^ 0x70);

	dx = x - rpcmouse_lastx;
	dy = y - rpcmouse_lasty;

	rpcmouse_lastx = x;
	rpcmouse_lasty = y;

	input_report_rel(dev, REL_X, dx);
	input_report_rel(dev, REL_Y, -dy);

	input_report_key(dev, BTN_LEFT,   b & 0x40);
	input_report_key(dev, BTN_MIDDLE, b & 0x20);
	input_report_key(dev, BTN_RIGHT,  b & 0x10);

	input_sync(dev);

	return IRQ_HANDLED;
}