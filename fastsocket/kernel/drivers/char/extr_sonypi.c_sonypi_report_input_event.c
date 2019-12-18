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
typedef  int u8 ;
struct sonypi_keypress {struct input_dev* dev; int /*<<< orphan*/  key; int /*<<< orphan*/ * member_0; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  kp ;
struct TYPE_4__ {int /*<<< orphan*/  input_work; int /*<<< orphan*/  input_fifo; struct input_dev* input_key_dev; struct input_dev* input_jog_dev; } ;
struct TYPE_3__ {int sonypiev; int /*<<< orphan*/  inputev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  REL_WHEEL ; 
#define  SONYPI_EVENT_FNKEY_RELEASED 133 
#define  SONYPI_EVENT_JOGDIAL_DOWN 132 
#define  SONYPI_EVENT_JOGDIAL_DOWN_PRESSED 131 
#define  SONYPI_EVENT_JOGDIAL_PRESSED 130 
#define  SONYPI_EVENT_JOGDIAL_UP 129 
#define  SONYPI_EVENT_JOGDIAL_UP_PRESSED 128 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_2__ sonypi_device ; 
 TYPE_1__* sonypi_inputkeys ; 

__attribute__((used)) static void sonypi_report_input_event(u8 event)
{
	struct input_dev *jog_dev = sonypi_device.input_jog_dev;
	struct input_dev *key_dev = sonypi_device.input_key_dev;
	struct sonypi_keypress kp = { NULL };
	int i;

	switch (event) {
	case SONYPI_EVENT_JOGDIAL_UP:
	case SONYPI_EVENT_JOGDIAL_UP_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, 1);
		input_sync(jog_dev);
		break;

	case SONYPI_EVENT_JOGDIAL_DOWN:
	case SONYPI_EVENT_JOGDIAL_DOWN_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, -1);
		input_sync(jog_dev);
		break;

	case SONYPI_EVENT_JOGDIAL_PRESSED:
		kp.key = BTN_MIDDLE;
		kp.dev = jog_dev;
		break;

	case SONYPI_EVENT_FNKEY_RELEASED:
		/* Nothing, not all VAIOs generate this event */
		break;

	default:
		for (i = 0; sonypi_inputkeys[i].sonypiev; i++)
			if (event == sonypi_inputkeys[i].sonypiev) {
				kp.dev = key_dev;
				kp.key = sonypi_inputkeys[i].inputev;
				break;
			}
		break;
	}

	if (kp.dev) {
		input_report_key(kp.dev, kp.key, 1);
		input_sync(kp.dev);
		kfifo_put(sonypi_device.input_fifo,
			  (unsigned char *)&kp, sizeof(kp));
		schedule_work(&sonypi_device.input_work);
	}
}