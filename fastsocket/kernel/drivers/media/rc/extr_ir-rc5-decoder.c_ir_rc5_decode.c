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
typedef  int u8 ;
typedef  int u32 ;
struct rc_dev {TYPE_1__* raw; } ;
struct rc5_dec {int state; int count; int wanted_bits; int bits; } ;
struct ir_raw_event {int /*<<< orphan*/  pulse; int /*<<< orphan*/  duration; scalar_t__ reset; } ;
struct TYPE_2__ {int enabled_protocols; int /*<<< orphan*/  prev_ev; struct rc5_dec rc5; } ;

/* Variables and functions */
 int CHECK_RC5X_NBITS ; 
 int EINVAL ; 
 int /*<<< orphan*/  IR_dprintk (int,char*,int,int,...) ; 
 void* RC5X_NBITS ; 
 int RC5X_SPACE ; 
 int RC5_BIT_END ; 
 int RC5_BIT_START ; 
 int RC5_NBITS ; 
 int RC5_UNIT ; 
 int RC_TYPE_RC5 ; 
#define  STATE_BIT_END 132 
#define  STATE_BIT_START 131 
#define  STATE_CHECK_RC5X 130 
#define  STATE_FINISHED 129 
#define  STATE_INACTIVE 128 
 int /*<<< orphan*/  TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrease_duration (struct ir_raw_event*,int) ; 
 int /*<<< orphan*/  eq_margin (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ geq_margin (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_timing_event (struct ir_raw_event) ; 
 int /*<<< orphan*/  is_transition (struct ir_raw_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int,int) ; 

__attribute__((used)) static int ir_rc5_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct rc5_dec *data = &dev->raw->rc5;
	u8 toggle;
	u32 scancode;

        if (!(dev->raw->enabled_protocols & RC_TYPE_RC5))
                return 0;

	if (!is_timing_event(ev)) {
		if (ev.reset)
			data->state = STATE_INACTIVE;
		return 0;
	}

	if (!geq_margin(ev.duration, RC5_UNIT, RC5_UNIT / 2))
		goto out;

again:
	IR_dprintk(2, "RC5(x) decode started at state %i (%uus %s)\n",
		   data->state, TO_US(ev.duration), TO_STR(ev.pulse));

	if (!geq_margin(ev.duration, RC5_UNIT, RC5_UNIT / 2))
		return 0;

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.pulse)
			break;

		data->state = STATE_BIT_START;
		data->count = 1;
		/* We just need enough bits to get to STATE_CHECK_RC5X */
		data->wanted_bits = RC5X_NBITS;
		decrease_duration(&ev, RC5_BIT_START);
		goto again;

	case STATE_BIT_START:
		if (!eq_margin(ev.duration, RC5_BIT_START, RC5_UNIT / 2))
			break;

		data->bits <<= 1;
		if (!ev.pulse)
			data->bits |= 1;
		data->count++;
		data->state = STATE_BIT_END;
		return 0;

	case STATE_BIT_END:
		if (!is_transition(&ev, &dev->raw->prev_ev))
			break;

		if (data->count == data->wanted_bits)
			data->state = STATE_FINISHED;
		else if (data->count == CHECK_RC5X_NBITS)
			data->state = STATE_CHECK_RC5X;
		else
			data->state = STATE_BIT_START;

		decrease_duration(&ev, RC5_BIT_END);
		goto again;

	case STATE_CHECK_RC5X:
		if (!ev.pulse && geq_margin(ev.duration, RC5X_SPACE, RC5_UNIT / 2)) {
			/* RC5X */
			data->wanted_bits = RC5X_NBITS;
			decrease_duration(&ev, RC5X_SPACE);
		} else {
			/* RC5 */
			data->wanted_bits = RC5_NBITS;
		}
		data->state = STATE_BIT_START;
		goto again;

	case STATE_FINISHED:
		if (ev.pulse)
			break;

		if (data->wanted_bits == RC5X_NBITS) {
			/* RC5X */
			u8 xdata, command, system;
			xdata    = (data->bits & 0x0003F) >> 0;
			command  = (data->bits & 0x00FC0) >> 6;
			system   = (data->bits & 0x1F000) >> 12;
			toggle   = (data->bits & 0x20000) ? 1 : 0;
			command += (data->bits & 0x01000) ? 0 : 0x40;
			scancode = system << 16 | command << 8 | xdata;

			IR_dprintk(1, "RC5X scancode 0x%06x (toggle: %u)\n",
				   scancode, toggle);

		} else {
			/* RC5 */
			u8 command, system;
			command  = (data->bits & 0x0003F) >> 0;
			system   = (data->bits & 0x007C0) >> 6;
			toggle   = (data->bits & 0x00800) ? 1 : 0;
			command += (data->bits & 0x01000) ? 0 : 0x40;
			scancode = system << 8 | command;

			IR_dprintk(1, "RC5 scancode 0x%04x (toggle: %u)\n",
				   scancode, toggle);
		}

		rc_keydown(dev, scancode, toggle);
		data->state = STATE_INACTIVE;
		return 0;
	}

out:
	IR_dprintk(1, "RC5(x) decode failed at state %i (%uus %s)\n",
		   data->state, TO_US(ev.duration), TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	return -EINVAL;
}