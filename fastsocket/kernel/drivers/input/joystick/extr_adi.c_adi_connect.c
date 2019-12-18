#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gameport_driver {int dummy; } ;
struct gameport {int dummy; } ;
struct adi_port {TYPE_1__* adi; struct gameport* gameport; } ;
struct TYPE_5__ {scalar_t__ ret; scalar_t__ length; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADI_DATA_DELAY ; 
 int /*<<< orphan*/  ADI_INIT_DELAY ; 
 scalar_t__ ADI_MIN_LEN_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GAMEPORT_MODE_RAW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  adi_get_bits (TYPE_1__*,int) ; 
 int /*<<< orphan*/  adi_id_decode (TYPE_1__*,struct adi_port*) ; 
 int /*<<< orphan*/  adi_init_center (TYPE_1__*) ; 
 int /*<<< orphan*/  adi_init_digital (struct gameport*) ; 
 int adi_init_input (TYPE_1__*,struct adi_port*,int) ; 
 int /*<<< orphan*/  adi_move_bits (struct adi_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adi_poll ; 
 scalar_t__ adi_read (struct adi_port*) ; 
 int /*<<< orphan*/  adi_read_packet (struct adi_port*) ; 
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 int gameport_open (struct gameport*,struct gameport_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,struct adi_port*) ; 
 int /*<<< orphan*/  gameport_set_poll_handler (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_poll_interval (struct gameport*,int) ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ *) ; 
 int input_register_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adi_port*) ; 
 struct adi_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adi_connect(struct gameport *gameport, struct gameport_driver *drv)
{
	struct adi_port *port;
	int i;
	int err;

	port = kzalloc(sizeof(struct adi_port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	port->gameport = gameport;

	gameport_set_drvdata(gameport, port);

	err = gameport_open(gameport, drv, GAMEPORT_MODE_RAW);
	if (err)
		goto fail1;

	adi_init_digital(gameport);
	adi_read_packet(port);

	if (port->adi[0].ret >= ADI_MIN_LEN_LENGTH)
		adi_move_bits(port, adi_get_bits(port->adi, 10));

	for (i = 0; i < 2; i++) {
		adi_id_decode(port->adi + i, port);

		if (!port->adi[i].length)
			continue;

		err = adi_init_input(port->adi + i, port, i);
		if (err)
			goto fail2;
	}

	if (!port->adi[0].length && !port->adi[1].length) {
		err = -ENODEV;
		goto fail2;
	}

	gameport_set_poll_handler(gameport, adi_poll);
	gameport_set_poll_interval(gameport, 20);

	msleep(ADI_INIT_DELAY);
	if (adi_read(port)) {
		msleep(ADI_DATA_DELAY);
		adi_read(port);
	}

	for (i = 0; i < 2; i++)
		if (port->adi[i].length > 0) {
			adi_init_center(port->adi + i);
			err = input_register_device(port->adi[i].dev);
			if (err)
				goto fail3;
		}

	return 0;

 fail3: while (--i >= 0) {
		if (port->adi[i].length > 0) {
			input_unregister_device(port->adi[i].dev);
			port->adi[i].dev = NULL;
		}
	}
 fail2:	for (i = 0; i < 2; i++)
		if (port->adi[i].dev)
			input_free_device(port->adi[i].dev);
	gameport_close(gameport);
 fail1:	gameport_set_drvdata(gameport, NULL);
	kfree(port);
	return err;
}