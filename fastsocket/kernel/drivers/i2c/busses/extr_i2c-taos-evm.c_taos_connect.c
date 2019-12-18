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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {TYPE_1__ dev; int /*<<< orphan*/  name; struct serio* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct taos_data {scalar_t__ state; int /*<<< orphan*/  client; int /*<<< orphan*/  buffer; int /*<<< orphan*/  pos; struct i2c_adapter adapter; } ;
struct serio_driver {int dummy; } ;
struct serio {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TAOS_CMD_ECHO_OFF ; 
 int /*<<< orphan*/  TAOS_CMD_RESET ; 
 scalar_t__ TAOS_STATE_EOFF ; 
 scalar_t__ TAOS_STATE_IDLE ; 
 scalar_t__ TAOS_STATE_INIT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  kfree (struct taos_data*) ; 
 struct taos_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct taos_data*) ; 
 int /*<<< orphan*/  serio_write (struct serio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 char* taos_adapter_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_algorithm ; 
 int /*<<< orphan*/  taos_instantiate_device (struct i2c_adapter*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int taos_connect(struct serio *serio, struct serio_driver *drv)
{
	struct taos_data *taos;
	struct i2c_adapter *adapter;
	char *name;
	int err;

	taos = kzalloc(sizeof(struct taos_data), GFP_KERNEL);
	if (!taos) {
		err = -ENOMEM;
		goto exit;
	}
	taos->state = TAOS_STATE_INIT;
	serio_set_drvdata(serio, taos);

	err = serio_open(serio, drv);
	if (err)
		goto exit_kfree;

	adapter = &taos->adapter;
	adapter->owner = THIS_MODULE;
	adapter->algo = &taos_algorithm;
	adapter->algo_data = serio;
	adapter->dev.parent = &serio->dev;

	/* Reset the TAOS evaluation module to identify it */
	serio_write(serio, TAOS_CMD_RESET);
	wait_event_interruptible_timeout(wq, taos->state == TAOS_STATE_IDLE,
					 msecs_to_jiffies(2000));

	if (taos->state != TAOS_STATE_IDLE) {
		err = -ENODEV;
		dev_dbg(&serio->dev, "TAOS EVM reset failed (state=%d, "
			"pos=%d)\n", taos->state, taos->pos);
		goto exit_close;
	}

	name = taos_adapter_name(taos->buffer);
	if (!name) {
		err = -ENODEV;
		dev_err(&serio->dev, "TAOS EVM identification failed\n");
		goto exit_close;
	}
	strlcpy(adapter->name, name, sizeof(adapter->name));

	/* Turn echo off for better performance */
	taos->state = TAOS_STATE_EOFF;
	serio_write(serio, TAOS_CMD_ECHO_OFF);

	wait_event_interruptible_timeout(wq, taos->state == TAOS_STATE_IDLE,
					 msecs_to_jiffies(250));
	if (taos->state != TAOS_STATE_IDLE) {
		err = -ENODEV;
		dev_err(&adapter->dev, "Echo off failed "
			"(state=%d)\n", taos->state);
		goto exit_close;
	}

	err = i2c_add_adapter(adapter);
	if (err)
		goto exit_close;
	dev_dbg(&serio->dev, "Connected to TAOS EVM\n");

	taos->client = taos_instantiate_device(adapter);
	return 0;

 exit_close:
	serio_close(serio);
 exit_kfree:
	serio_set_drvdata(serio, NULL);
	kfree(taos);
 exit:
	return err;
}