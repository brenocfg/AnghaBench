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
typedef  int u32 ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct rc_dev {struct mceusb_dev* priv; } ;
struct mceusb_dev {unsigned char tx_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MCE_CMDBUF_SIZE ; 
 unsigned char MCE_CMD_S_TXMASK ; 
 int MCE_CODE_LENGTH ; 
 unsigned char MCE_COMMAND_HEADER ; 
 unsigned char MCE_COMMAND_IRDATA ; 
 unsigned char MCE_IRDATA_HEADER ; 
 unsigned char MCE_IRDATA_TRAILER ; 
 int MCE_MAX_PULSE_LENGTH ; 
 int MCE_PULSE_BIT ; 
 int MCE_TIME_UNIT ; 
 int MCE_TX_HEADER_LENGTH ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_async_out (struct mceusb_dev*,unsigned char*,int) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (long) ; 

__attribute__((used)) static int mceusb_tx_ir(struct rc_dev *dev, int *txbuf, u32 n)
{
	struct mceusb_dev *ir = dev->priv;
	int i, ret = 0;
	int count, cmdcount = 0;
	unsigned char *cmdbuf; /* MCE command buffer */
	long signal_duration = 0; /* Singnal length in us */
	struct timeval start_time, end_time;

	do_gettimeofday(&start_time);

	count = n / sizeof(int);

	cmdbuf = kzalloc(sizeof(int) * MCE_CMDBUF_SIZE, GFP_KERNEL);
	if (!cmdbuf)
		return -ENOMEM;

	/* MCE tx init header */
	cmdbuf[cmdcount++] = MCE_COMMAND_HEADER;
	cmdbuf[cmdcount++] = MCE_CMD_S_TXMASK;
	cmdbuf[cmdcount++] = ir->tx_mask;

	/* Generate mce packet data */
	for (i = 0; (i < count) && (cmdcount < MCE_CMDBUF_SIZE); i++) {
		signal_duration += txbuf[i];
		txbuf[i] = txbuf[i] / MCE_TIME_UNIT;

		do { /* loop to support long pulses/spaces > 127*50us=6.35ms */

			/* Insert mce packet header every 4th entry */
			if ((cmdcount < MCE_CMDBUF_SIZE) &&
			    (cmdcount - MCE_TX_HEADER_LENGTH) %
			     MCE_CODE_LENGTH == 0)
				cmdbuf[cmdcount++] = MCE_IRDATA_HEADER;

			/* Insert mce packet data */
			if (cmdcount < MCE_CMDBUF_SIZE)
				cmdbuf[cmdcount++] =
					(txbuf[i] < MCE_PULSE_BIT ?
					 txbuf[i] : MCE_MAX_PULSE_LENGTH) |
					 (i & 1 ? 0x00 : MCE_PULSE_BIT);
			else {
				ret = -EINVAL;
				goto out;
			}

		} while ((txbuf[i] > MCE_MAX_PULSE_LENGTH) &&
			 (txbuf[i] -= MCE_MAX_PULSE_LENGTH));
	}

	/* Fix packet length in last header */
	cmdbuf[cmdcount - (cmdcount - MCE_TX_HEADER_LENGTH) % MCE_CODE_LENGTH] =
		MCE_COMMAND_IRDATA + (cmdcount - MCE_TX_HEADER_LENGTH) %
		MCE_CODE_LENGTH - 1;

	/* Check if we have room for the empty packet at the end */
	if (cmdcount >= MCE_CMDBUF_SIZE) {
		ret = -EINVAL;
		goto out;
	}

	/* All mce commands end with an empty packet (0x80) */
	cmdbuf[cmdcount++] = MCE_IRDATA_TRAILER;

	/* Transmit the command to the mce device */
	mce_async_out(ir, cmdbuf, cmdcount);

	/*
	 * The lircd gap calculation expects the write function to
	 * wait the time it takes for the ircommand to be sent before
	 * it returns.
	 */
	do_gettimeofday(&end_time);
	signal_duration -= (end_time.tv_usec - start_time.tv_usec) +
			   (end_time.tv_sec - start_time.tv_sec) * 1000000;

	/* delay with the closest number of ticks */
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(usecs_to_jiffies(signal_duration));

out:
	kfree(cmdbuf);
	return ret ? ret : n;
}