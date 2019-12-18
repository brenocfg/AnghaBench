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
struct rc_dev {int /*<<< orphan*/  keypressed; TYPE_1__* raw; } ;
struct nec_dec {int state; int is_nec_x; int necx_repeat; int bits; int /*<<< orphan*/  count; } ;
struct ir_raw_event {int /*<<< orphan*/  pulse; int /*<<< orphan*/  duration; scalar_t__ reset; } ;
struct TYPE_2__ {int enabled_protocols; struct nec_dec nec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IR_dprintk (int,char*,...) ; 
 int /*<<< orphan*/  NECX_HEADER_PULSE ; 
 int /*<<< orphan*/  NECX_REPEAT_BITS ; 
 int /*<<< orphan*/  NEC_BIT_0_SPACE ; 
 int /*<<< orphan*/  NEC_BIT_1_SPACE ; 
 int /*<<< orphan*/  NEC_BIT_PULSE ; 
 int /*<<< orphan*/  NEC_HEADER_PULSE ; 
 int /*<<< orphan*/  NEC_HEADER_SPACE ; 
 int /*<<< orphan*/  NEC_NBITS ; 
 int /*<<< orphan*/  NEC_REPEAT_SPACE ; 
 int /*<<< orphan*/  NEC_TRAILER_PULSE ; 
 int /*<<< orphan*/  NEC_TRAILER_SPACE ; 
 int NEC_UNIT ; 
 int RC_TYPE_NEC ; 
#define  STATE_BIT_PULSE 133 
#define  STATE_BIT_SPACE 132 
#define  STATE_HEADER_SPACE 131 
#define  STATE_INACTIVE 130 
#define  STATE_TRAILER_PULSE 129 
#define  STATE_TRAILER_SPACE 128 
 int /*<<< orphan*/  TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_US (int /*<<< orphan*/ ) ; 
 int bitrev8 (int) ; 
 int /*<<< orphan*/  eq_margin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  geq_margin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_timing_event (struct ir_raw_event) ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_repeat (struct rc_dev*) ; 

__attribute__((used)) static int ir_nec_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct nec_dec *data = &dev->raw->nec;
	u32 scancode;
	u8 address, not_address, command, not_command;

	if (!(dev->raw->enabled_protocols & RC_TYPE_NEC))
		return 0;

	if (!is_timing_event(ev)) {
		if (ev.reset)
			data->state = STATE_INACTIVE;
		return 0;
	}

	IR_dprintk(2, "NEC decode started at state %d (%uus %s)\n",
		   data->state, TO_US(ev.duration), TO_STR(ev.pulse));

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.pulse)
			break;

		if (eq_margin(ev.duration, NEC_HEADER_PULSE, NEC_UNIT / 2)) {
			data->is_nec_x = false;
			data->necx_repeat = false;
		} else if (eq_margin(ev.duration, NECX_HEADER_PULSE, NEC_UNIT / 2))
			data->is_nec_x = true;
		else
			break;

		data->count = 0;
		data->state = STATE_HEADER_SPACE;
		return 0;

	case STATE_HEADER_SPACE:
		if (ev.pulse)
			break;

		if (eq_margin(ev.duration, NEC_HEADER_SPACE, NEC_UNIT / 2)) {
			data->state = STATE_BIT_PULSE;
			return 0;
		} else if (eq_margin(ev.duration, NEC_REPEAT_SPACE, NEC_UNIT / 2)) {
			if (!dev->keypressed) {
				IR_dprintk(1, "Discarding last key repeat: event after key up\n");
			} else {
				rc_repeat(dev);
				IR_dprintk(1, "Repeat last key\n");
				data->state = STATE_TRAILER_PULSE;
			}
			return 0;
		}

		break;

	case STATE_BIT_PULSE:
		if (!ev.pulse)
			break;

		if (!eq_margin(ev.duration, NEC_BIT_PULSE, NEC_UNIT / 2))
			break;

		data->state = STATE_BIT_SPACE;
		return 0;

	case STATE_BIT_SPACE:
		if (ev.pulse)
			break;

		if (data->necx_repeat && data->count == NECX_REPEAT_BITS &&
			geq_margin(ev.duration,
			NEC_TRAILER_SPACE, NEC_UNIT / 2)) {
				IR_dprintk(1, "Repeat last key\n");
				rc_repeat(dev);
				data->state = STATE_INACTIVE;
				return 0;

		} else if (data->count > NECX_REPEAT_BITS)
			data->necx_repeat = false;

		data->bits <<= 1;
		if (eq_margin(ev.duration, NEC_BIT_1_SPACE, NEC_UNIT / 2))
			data->bits |= 1;
		else if (!eq_margin(ev.duration, NEC_BIT_0_SPACE, NEC_UNIT / 2))
			break;
		data->count++;

		if (data->count == NEC_NBITS)
			data->state = STATE_TRAILER_PULSE;
		else
			data->state = STATE_BIT_PULSE;

		return 0;

	case STATE_TRAILER_PULSE:
		if (!ev.pulse)
			break;

		if (!eq_margin(ev.duration, NEC_TRAILER_PULSE, NEC_UNIT / 2))
			break;

		data->state = STATE_TRAILER_SPACE;
		return 0;

	case STATE_TRAILER_SPACE:
		if (ev.pulse)
			break;

		if (!geq_margin(ev.duration, NEC_TRAILER_SPACE, NEC_UNIT / 2))
			break;

		address     = bitrev8((data->bits >> 24) & 0xff);
		not_address = bitrev8((data->bits >> 16) & 0xff);
		command	    = bitrev8((data->bits >>  8) & 0xff);
		not_command = bitrev8((data->bits >>  0) & 0xff);

		if ((command ^ not_command) != 0xff) {
			IR_dprintk(1, "NEC checksum error: received 0x%08x\n",
				   data->bits);
			break;
		}

		if ((address ^ not_address) != 0xff) {
			/* Extended NEC */
			scancode = address     << 16 |
				   not_address <<  8 |
				   command;
			IR_dprintk(1, "NEC (Ext) scancode 0x%06x\n", scancode);
		} else {
			/* Normal NEC */
			scancode = address << 8 | command;
			IR_dprintk(1, "NEC scancode 0x%04x\n", scancode);
		}

		if (data->is_nec_x)
			data->necx_repeat = true;

		rc_keydown(dev, scancode, 0);
		data->state = STATE_INACTIVE;
		return 0;
	}

	IR_dprintk(1, "NEC decode failed at state %d (%uus %s)\n",
		   data->state, TO_US(ev.duration), TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	return -EINVAL;
}