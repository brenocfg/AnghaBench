#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int product; int version; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct grip_port {size_t mode; int registered; scalar_t__ dirty; struct input_dev* dev; } ;
struct grip_mp {TYPE_3__* gameport; struct grip_port** port; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_GAMEPORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GAMEPORT_ID_VENDOR_GRAVIS ; 
 int** grip_abs ; 
 int** grip_btn ; 
 int /*<<< orphan*/  grip_close ; 
 int /*<<< orphan*/ * grip_name ; 
 int /*<<< orphan*/  grip_open ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct grip_mp*) ; 
 int /*<<< orphan*/  report_slot (struct grip_mp*,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int register_slot(int slot, struct grip_mp *grip)
{
	struct grip_port *port = grip->port[slot];
	struct input_dev *input_dev;
	int j, t;
	int err;

	port->dev = input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = grip_name[port->mode];
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.vendor = GAMEPORT_ID_VENDOR_GRAVIS;
	input_dev->id.product = 0x0100 + port->mode;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &grip->gameport->dev;

	input_set_drvdata(input_dev, grip);

	input_dev->open = grip_open;
	input_dev->close = grip_close;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	for (j = 0; (t = grip_abs[port->mode][j]) >= 0; j++)
		input_set_abs_params(input_dev, t, -1, 1, 0, 0);

	for (j = 0; (t = grip_btn[port->mode][j]) >= 0; j++)
		if (t > 0)
			set_bit(t, input_dev->keybit);

	err = input_register_device(port->dev);
	if (err) {
		input_free_device(port->dev);
		return err;
	}

	port->registered = 1;

	if (port->dirty)	            /* report initial state, if any */
		report_slot(grip, slot);

	return 0;
}