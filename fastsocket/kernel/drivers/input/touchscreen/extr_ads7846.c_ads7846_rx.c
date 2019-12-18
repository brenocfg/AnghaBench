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
typedef  unsigned int u16 ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {unsigned int x; unsigned int y; unsigned int z1; unsigned int z2; scalar_t__ ignore; } ;
struct ads7846_packet {TYPE_1__ tc; } ;
struct ads7846 {int model; int pressure_max; unsigned int x_plate_ohms; int pendown; int /*<<< orphan*/  timer; TYPE_2__* spi; scalar_t__ swap_xy; struct input_dev* input; scalar_t__ penirq_recheck_delay_usecs; struct ads7846_packet* packet; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 unsigned int MAX_12BIT ; 
 int /*<<< orphan*/  TS_POLL_PERIOD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_pendown_state (struct ads7846*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static void ads7846_rx(void *ads)
{
	struct ads7846		*ts = ads;
	struct ads7846_packet	*packet = ts->packet;
	unsigned		Rt;
	u16			x, y, z1, z2;

	/* ads7846_rx_val() did in-place conversion (including byteswap) from
	 * on-the-wire format as part of debouncing to get stable readings.
	 */
	x = packet->tc.x;
	y = packet->tc.y;
	z1 = packet->tc.z1;
	z2 = packet->tc.z2;

	/* range filtering */
	if (x == MAX_12BIT)
		x = 0;

	if (ts->model == 7843) {
		Rt = ts->pressure_max / 2;
	} else if (likely(x && z1)) {
		/* compute touch pressure resistance using equation #2 */
		Rt = z2;
		Rt -= z1;
		Rt *= x;
		Rt *= ts->x_plate_ohms;
		Rt /= z1;
		Rt = (Rt + 2047) >> 12;
	} else {
		Rt = 0;
	}

	/* Sample found inconsistent by debouncing or pressure is beyond
	 * the maximum. Don't report it to user space, repeat at least
	 * once more the measurement
	 */
	if (packet->tc.ignore || Rt > ts->pressure_max) {
#ifdef VERBOSE
		pr_debug("%s: ignored %d pressure %d\n",
			dev_name(&ts->spi->dev), packet->tc.ignore, Rt);
#endif
		hrtimer_start(&ts->timer, ktime_set(0, TS_POLL_PERIOD),
			      HRTIMER_MODE_REL);
		return;
	}

	/* Maybe check the pendown state before reporting. This discards
	 * false readings when the pen is lifted.
	 */
	if (ts->penirq_recheck_delay_usecs) {
		udelay(ts->penirq_recheck_delay_usecs);
		if (!get_pendown_state(ts))
			Rt = 0;
	}

	/* NOTE: We can't rely on the pressure to determine the pen down
	 * state, even this controller has a pressure sensor.  The pressure
	 * value can fluctuate for quite a while after lifting the pen and
	 * in some cases may not even settle at the expected value.
	 *
	 * The only safe way to check for the pen up condition is in the
	 * timer by reading the pen signal state (it's a GPIO _and_ IRQ).
	 */
	if (Rt) {
		struct input_dev *input = ts->input;

		if (!ts->pendown) {
			input_report_key(input, BTN_TOUCH, 1);
			ts->pendown = 1;
#ifdef VERBOSE
			dev_dbg(&ts->spi->dev, "DOWN\n");
#endif
		}

		if (ts->swap_xy)
			swap(x, y);

		input_report_abs(input, ABS_X, x);
		input_report_abs(input, ABS_Y, y);
		input_report_abs(input, ABS_PRESSURE, Rt);

		input_sync(input);
#ifdef VERBOSE
		dev_dbg(&ts->spi->dev, "%4d/%4d/%4d\n", x, y, Rt);
#endif
	}

	hrtimer_start(&ts->timer, ktime_set(0, TS_POLL_PERIOD),
			HRTIMER_MODE_REL);
}