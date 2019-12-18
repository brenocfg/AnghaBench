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
struct tmdc {int exists; struct tmdc** port; int /*<<< orphan*/  dev; struct gameport* gameport; } ;
struct gameport_driver {int dummy; } ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GAMEPORT_MODE_RAW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TMDC_MAX_LENGTH ; 
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 int gameport_open (struct gameport*,struct gameport_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,struct tmdc*) ; 
 int /*<<< orphan*/  gameport_set_poll_handler (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_poll_interval (struct gameport*,int) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tmdc*) ; 
 struct tmdc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmdc_poll ; 
 int tmdc_read_packet (struct gameport*,unsigned char**) ; 
 int tmdc_setup_port (struct tmdc*,int,unsigned char*) ; 

__attribute__((used)) static int tmdc_connect(struct gameport *gameport, struct gameport_driver *drv)
{
	unsigned char data[2][TMDC_MAX_LENGTH];
	struct tmdc *tmdc;
	int i;
	int err;

	if (!(tmdc = kzalloc(sizeof(struct tmdc), GFP_KERNEL)))
		return -ENOMEM;

	tmdc->gameport = gameport;

	gameport_set_drvdata(gameport, tmdc);

	err = gameport_open(gameport, drv, GAMEPORT_MODE_RAW);
	if (err)
		goto fail1;

	if (!(tmdc->exists = tmdc_read_packet(gameport, data))) {
		err = -ENODEV;
		goto fail2;
	}

	gameport_set_poll_handler(gameport, tmdc_poll);
	gameport_set_poll_interval(gameport, 20);

	for (i = 0; i < 2; i++) {
		if (tmdc->exists & (1 << i)) {

			err = tmdc_setup_port(tmdc, i, data[i]);
			if (err)
				goto fail3;
		}
	}

	return 0;

 fail3: while (--i >= 0) {
		if (tmdc->port[i]) {
			input_unregister_device(tmdc->port[i]->dev);
			kfree(tmdc->port[i]);
		}
	}
 fail2:	gameport_close(gameport);
 fail1:	gameport_set_drvdata(gameport, NULL);
	kfree(tmdc);
	return err;
}