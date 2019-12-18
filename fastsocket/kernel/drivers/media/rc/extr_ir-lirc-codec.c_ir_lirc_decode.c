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
typedef  int /*<<< orphan*/  u64 ;
struct rc_dev {TYPE_2__* raw; } ;
struct lirc_codec {int gap; int gap_duration; TYPE_1__* drv; int /*<<< orphan*/  gap_start; int /*<<< orphan*/  send_timeout_reports; } ;
struct ir_raw_event {int duration; scalar_t__ pulse; scalar_t__ timeout; int /*<<< orphan*/  carrier; scalar_t__ carrier_report; scalar_t__ reset; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait_poll; } ;
struct TYPE_5__ {int enabled_protocols; struct lirc_codec lirc; } ;
struct TYPE_4__ {TYPE_3__* rbuf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IR_dprintk (int,char*,int,...) ; 
 int LIRC_FREQUENCY (int /*<<< orphan*/ ) ; 
 int LIRC_PULSE (int) ; 
 int LIRC_SPACE (int) ; 
 int LIRC_TIMEOUT (int) ; 
 scalar_t__ LIRC_VALUE_MASK ; 
 int RC_TYPE_LIRC ; 
 int /*<<< orphan*/  TO_STR (scalar_t__) ; 
 int /*<<< orphan*/  TO_US (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lirc_buffer_write (TYPE_3__*,unsigned char*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ir_lirc_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct lirc_codec *lirc = &dev->raw->lirc;
	int sample;

	if (!(dev->raw->enabled_protocols & RC_TYPE_LIRC))
		return 0;

	if (!dev->raw->lirc.drv || !dev->raw->lirc.drv->rbuf)
		return -EINVAL;

	/* Packet start */
	if (ev.reset)
		return 0;

	/* Carrier reports */
	if (ev.carrier_report) {
		sample = LIRC_FREQUENCY(ev.carrier);
		IR_dprintk(2, "carrier report (freq: %d)\n", sample);

	/* Packet end */
	} else if (ev.timeout) {

		if (lirc->gap)
			return 0;

		lirc->gap_start = ktime_get();
		lirc->gap = true;
		lirc->gap_duration = ev.duration;

		if (!lirc->send_timeout_reports)
			return 0;

		sample = LIRC_TIMEOUT(ev.duration / 1000);
		IR_dprintk(2, "timeout report (duration: %d)\n", sample);

	/* Normal sample */
	} else {

		if (lirc->gap) {
			int gap_sample;

			lirc->gap_duration += ktime_to_ns(ktime_sub(ktime_get(),
				lirc->gap_start));

			/* Convert to ms and cap by LIRC_VALUE_MASK */
			do_div(lirc->gap_duration, 1000);
			lirc->gap_duration = min(lirc->gap_duration,
							(u64)LIRC_VALUE_MASK);

			gap_sample = LIRC_SPACE(lirc->gap_duration);
			lirc_buffer_write(dev->raw->lirc.drv->rbuf,
						(unsigned char *) &gap_sample);
			lirc->gap = false;
		}

		sample = ev.pulse ? LIRC_PULSE(ev.duration / 1000) :
					LIRC_SPACE(ev.duration / 1000);
		IR_dprintk(2, "delivering %uus %s to lirc_dev\n",
			   TO_US(ev.duration), TO_STR(ev.pulse));
	}

	lirc_buffer_write(dev->raw->lirc.drv->rbuf,
			  (unsigned char *) &sample);
	wake_up(&dev->raw->lirc.drv->rbuf->wait_poll);

	return 0;
}