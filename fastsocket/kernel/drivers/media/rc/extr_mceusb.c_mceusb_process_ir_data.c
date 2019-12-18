#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ microsoft_gen1; } ;
struct mceusb_dev {int parser_state; int rem; int cmd; int* buf_in; int /*<<< orphan*/  rc; int /*<<< orphan*/  dev; TYPE_1__ flags; } ;
struct TYPE_7__ {int pulse; int duration; } ;

/* Variables and functions */
#define  CMD_DATA 131 
#define  CMD_HEADER 130 
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_2__) ; 
 int MCE_COMMAND_HEADER ; 
 int MCE_COMMAND_IRDATA ; 
 int MCE_COMMAND_MASK ; 
 int MCE_PACKET_LENGTH_MASK ; 
 int MCE_PULSE_BIT ; 
 int MCE_PULSE_MASK ; 
 int /*<<< orphan*/  MCE_TIME_UNIT ; 
#define  PARSE_IRDATA 129 
#define  SUBCMD 128 
 int US_TO_NS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_ir_raw_event (TYPE_2__*) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int mceusb_cmdsize (int,int) ; 
 int /*<<< orphan*/  mceusb_dev_printdata (struct mceusb_dev*,int*,int,int,int) ; 
 int /*<<< orphan*/  mceusb_handle_command (struct mceusb_dev*,int) ; 
 TYPE_2__ rawir ; 

__attribute__((used)) static void mceusb_process_ir_data(struct mceusb_dev *ir, int buf_len)
{
	DEFINE_IR_RAW_EVENT(rawir);
	int i = 0;

	/* skip meaningless 0xb1 0x60 header bytes on orig receiver */
	if (ir->flags.microsoft_gen1)
		i = 2;

	/* if there's no data, just return now */
	if (buf_len <= i)
		return;

	for (; i < buf_len; i++) {
		switch (ir->parser_state) {
		case SUBCMD:
			ir->rem = mceusb_cmdsize(ir->cmd, ir->buf_in[i]);
			mceusb_dev_printdata(ir, ir->buf_in, i - 1,
					     ir->rem + 2, false);
			mceusb_handle_command(ir, i);
			ir->parser_state = CMD_DATA;
			break;
		case PARSE_IRDATA:
			ir->rem--;
			init_ir_raw_event(&rawir);
			rawir.pulse = ((ir->buf_in[i] & MCE_PULSE_BIT) != 0);
			rawir.duration = (ir->buf_in[i] & MCE_PULSE_MASK)
					 * US_TO_NS(MCE_TIME_UNIT);

			dev_dbg(ir->dev, "Storing %s with duration %d\n",
				rawir.pulse ? "pulse" : "space",
				rawir.duration);

			ir_raw_event_store_with_filter(ir->rc, &rawir);
			break;
		case CMD_DATA:
			ir->rem--;
			break;
		case CMD_HEADER:
			/* decode mce packets of the form (84),AA,BB,CC,DD */
			/* IR data packets can span USB messages - rem */
			ir->cmd = ir->buf_in[i];
			if ((ir->cmd == MCE_COMMAND_HEADER) ||
			    ((ir->cmd & MCE_COMMAND_MASK) !=
			     MCE_COMMAND_IRDATA)) {
				ir->parser_state = SUBCMD;
				continue;
			}
			ir->rem = (ir->cmd & MCE_PACKET_LENGTH_MASK);
			mceusb_dev_printdata(ir, ir->buf_in,
					     i, ir->rem + 1, false);
			if (ir->rem)
				ir->parser_state = PARSE_IRDATA;
			else
				ir_raw_event_reset(ir->rc);
			break;
		}

		if (ir->parser_state != CMD_HEADER && !ir->rem)
			ir->parser_state = CMD_HEADER;
	}
	dev_dbg(ir->dev, "processed IR data, calling ir_raw_event_handle\n");
	ir_raw_event_handle(ir->rc);
}