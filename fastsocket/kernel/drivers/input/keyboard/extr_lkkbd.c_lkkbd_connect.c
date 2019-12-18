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
struct serio_driver {int dummy; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; } ;
struct lkkbd {struct serio* serio; struct input_dev* dev; int /*<<< orphan*/ * keycode; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  ctrlclick_volume; int /*<<< orphan*/  keyclick_volume; int /*<<< orphan*/  bell_volume; int /*<<< orphan*/  tq; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int version; scalar_t__ product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {int keycodesize; int keycodemax; int /*<<< orphan*/  keybit; int /*<<< orphan*/ * keycode; int /*<<< orphan*/  sndbit; int /*<<< orphan*/  ledbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  event; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  lk_keycode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RS232 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_LED ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  LED_COMPOSE ; 
 int /*<<< orphan*/  LED_SCROLLL ; 
 int /*<<< orphan*/  LED_SLEEP ; 
 int /*<<< orphan*/  LK_CMD_POWERCYCLE_RESET ; 
 int LK_NUM_KEYCODES ; 
 int /*<<< orphan*/  SERIO_LKKBD ; 
 int /*<<< orphan*/  SND_BELL ; 
 int /*<<< orphan*/  SND_CLICK ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bell_volume ; 
 int /*<<< orphan*/  ctrlclick_volume ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct lkkbd*) ; 
 int /*<<< orphan*/  keyclick_volume ; 
 int /*<<< orphan*/  kfree (struct lkkbd*) ; 
 struct lkkbd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lkkbd_event ; 
 int /*<<< orphan*/  lkkbd_keycode ; 
 int /*<<< orphan*/  lkkbd_reinit ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct lkkbd*) ; 
 int /*<<< orphan*/  serio_write (struct serio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lkkbd_connect (struct serio *serio, struct serio_driver *drv)
{
	struct lkkbd *lk;
	struct input_dev *input_dev;
	int i;
	int err;

	lk = kzalloc (sizeof (struct lkkbd), GFP_KERNEL);
	input_dev = input_allocate_device ();
	if (!lk || !input_dev) {
		err = -ENOMEM;
		goto fail1;
	}

	lk->serio = serio;
	lk->dev = input_dev;
	INIT_WORK (&lk->tq, lkkbd_reinit);
	lk->bell_volume = bell_volume;
	lk->keyclick_volume = keyclick_volume;
	lk->ctrlclick_volume = ctrlclick_volume;
	memcpy (lk->keycode, lkkbd_keycode, sizeof (lk_keycode_t) * LK_NUM_KEYCODES);

	strlcpy (lk->name, "DEC LK keyboard", sizeof(lk->name));
	snprintf (lk->phys, sizeof(lk->phys), "%s/input0", serio->phys);

	input_dev->name = lk->name;
	input_dev->phys = lk->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.vendor = SERIO_LKKBD;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;
	input_dev->event = lkkbd_event;

	input_set_drvdata (input_dev, lk);

	set_bit (EV_KEY, input_dev->evbit);
	set_bit (EV_LED, input_dev->evbit);
	set_bit (EV_SND, input_dev->evbit);
	set_bit (EV_REP, input_dev->evbit);
	set_bit (LED_CAPSL, input_dev->ledbit);
	set_bit (LED_SLEEP, input_dev->ledbit);
	set_bit (LED_COMPOSE, input_dev->ledbit);
	set_bit (LED_SCROLLL, input_dev->ledbit);
	set_bit (SND_BELL, input_dev->sndbit);
	set_bit (SND_CLICK, input_dev->sndbit);

	input_dev->keycode = lk->keycode;
	input_dev->keycodesize = sizeof (lk_keycode_t);
	input_dev->keycodemax = LK_NUM_KEYCODES;

	for (i = 0; i < LK_NUM_KEYCODES; i++)
		__set_bit (lk->keycode[i], input_dev->keybit);
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	serio_set_drvdata (serio, lk);

	err = serio_open (serio, drv);
	if (err)
		goto fail2;

	err = input_register_device (lk->dev);
	if (err)
		goto fail3;

	serio_write (lk->serio, LK_CMD_POWERCYCLE_RESET);

	return 0;

 fail3:	serio_close (serio);
 fail2:	serio_set_drvdata (serio, NULL);
 fail1:	input_free_device (input_dev);
	kfree (lk);
	return err;
}