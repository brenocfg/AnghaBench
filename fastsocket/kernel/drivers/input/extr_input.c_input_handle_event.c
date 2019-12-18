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
struct input_dev {int sync; int* rep; int /*<<< orphan*/  (* event ) (struct input_dev*,unsigned int,unsigned int,int) ;int /*<<< orphan*/  snd; int /*<<< orphan*/  sndbit; int /*<<< orphan*/  led; int /*<<< orphan*/  ledbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  sw; int /*<<< orphan*/  swbit; int /*<<< orphan*/  key; int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MAX ; 
#define  EV_ABS 141 
#define  EV_FF 140 
#define  EV_KEY 139 
#define  EV_LED 138 
#define  EV_MSC 137 
#define  EV_PWR 136 
#define  EV_REL 135 
#define  EV_REP 134 
#define  EV_SND 133 
#define  EV_SW 132 
#define  EV_SYN 131 
 int INPUT_IGNORE_EVENT ; 
 int INPUT_PASS_TO_ALL ; 
 int INPUT_PASS_TO_DEVICE ; 
 int INPUT_PASS_TO_HANDLERS ; 
 int /*<<< orphan*/  KEY_MAX ; 
 int /*<<< orphan*/  LED_MAX ; 
 int /*<<< orphan*/  MSC_MAX ; 
 int /*<<< orphan*/  REL_MAX ; 
 unsigned int REP_MAX ; 
 int /*<<< orphan*/  SND_MAX ; 
 int /*<<< orphan*/  SW_MAX ; 
#define  SYN_CONFIG 130 
#define  SYN_MT_REPORT 129 
#define  SYN_REPORT 128 
 int /*<<< orphan*/  __change_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int input_handle_abs_event (struct input_dev*,unsigned int,int*) ; 
 int /*<<< orphan*/  input_pass_event (struct input_dev*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  input_start_autorepeat (struct input_dev*,unsigned int) ; 
 int /*<<< orphan*/  input_stop_autorepeat (struct input_dev*) ; 
 int /*<<< orphan*/  is_event_supported (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct input_dev*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_handle_event(struct input_dev *dev,
			       unsigned int type, unsigned int code, int value)
{
	int disposition = INPUT_IGNORE_EVENT;

	switch (type) {

	case EV_SYN:
		switch (code) {
		case SYN_CONFIG:
			disposition = INPUT_PASS_TO_ALL;
			break;

		case SYN_REPORT:
			if (!dev->sync) {
				dev->sync = 1;
				disposition = INPUT_PASS_TO_HANDLERS;
			}
			break;
		case SYN_MT_REPORT:
			dev->sync = 0;
			disposition = INPUT_PASS_TO_HANDLERS;
			break;
		}
		break;

	case EV_KEY:
		if (is_event_supported(code, dev->keybit, KEY_MAX) &&
		    !!test_bit(code, dev->key) != value) {

			if (value != 2) {
				__change_bit(code, dev->key);
				if (value)
					input_start_autorepeat(dev, code);
				else
					input_stop_autorepeat(dev);
			}

			disposition = INPUT_PASS_TO_HANDLERS;
		}
		break;

	case EV_SW:
		if (is_event_supported(code, dev->swbit, SW_MAX) &&
		    !!test_bit(code, dev->sw) != value) {

			__change_bit(code, dev->sw);
			disposition = INPUT_PASS_TO_HANDLERS;
		}
		break;

	case EV_ABS:
		if (is_event_supported(code, dev->absbit, ABS_MAX))
			disposition = input_handle_abs_event(dev, code, &value);

		break;

	case EV_REL:
		if (is_event_supported(code, dev->relbit, REL_MAX) && value)
			disposition = INPUT_PASS_TO_HANDLERS;

		break;

	case EV_MSC:
		if (is_event_supported(code, dev->mscbit, MSC_MAX))
			disposition = INPUT_PASS_TO_ALL;

		break;

	case EV_LED:
		if (is_event_supported(code, dev->ledbit, LED_MAX) &&
		    !!test_bit(code, dev->led) != value) {

			__change_bit(code, dev->led);
			disposition = INPUT_PASS_TO_ALL;
		}
		break;

	case EV_SND:
		if (is_event_supported(code, dev->sndbit, SND_MAX)) {

			if (!!test_bit(code, dev->snd) != !!value)
				__change_bit(code, dev->snd);
			disposition = INPUT_PASS_TO_ALL;
		}
		break;

	case EV_REP:
		if (code <= REP_MAX && value >= 0 && dev->rep[code] != value) {
			dev->rep[code] = value;
			disposition = INPUT_PASS_TO_ALL;
		}
		break;

	case EV_FF:
		if (value >= 0)
			disposition = INPUT_PASS_TO_ALL;
		break;

	case EV_PWR:
		disposition = INPUT_PASS_TO_ALL;
		break;
	}

	if (disposition != INPUT_IGNORE_EVENT && type != EV_SYN)
		dev->sync = 0;

	if ((disposition & INPUT_PASS_TO_DEVICE) && dev->event)
		dev->event(dev, type, code, value);

	if (disposition & INPUT_PASS_TO_HANDLERS)
		input_pass_event(dev, type, code, value);
}