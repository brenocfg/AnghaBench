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
struct workqueue_struct {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int id; int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; int /*<<< orphan*/  fw_wait; int /*<<< orphan*/  fw_work; } ;

/* Variables and functions */
 int CX25840_AUD_INT_CTRL_REG ; 
 int CX25840_AUD_INT_STAT_REG ; 
 int CX25840_VID_INT_STAT_REG ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
#define  V4L2_IDENT_CX23885_AV 130 
#define  V4L2_IDENT_CX23887_AV 129 
#define  V4L2_IDENT_CX23888_AV 128 
 struct workqueue_struct* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_std_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_work_handler ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_input (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void cx23885_initialize(struct i2c_client *client)
{
	DEFINE_WAIT(wait);
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	struct workqueue_struct *q;

	/*
	 * Come out of digital power down
	 * The CX23888, at least, needs this, otherwise registers aside from
	 * 0x0-0x2 can't be read or written.
	 */
	cx25840_write(client, 0x000, 0);

	/* Internal Reset */
	cx25840_and_or(client, 0x102, ~0x01, 0x01);
	cx25840_and_or(client, 0x102, ~0x01, 0x00);

	/* Stop microcontroller */
	cx25840_and_or(client, 0x803, ~0x10, 0x00);

	/* DIF in reset? */
	cx25840_write(client, 0x398, 0);

	/*
	 * Trust the default xtal, no division
	 * '885: 28.636363... MHz
	 * '887: 25.000000 MHz
	 * '888: 50.000000 MHz
	 */
	cx25840_write(client, 0x2, 0x76);

	/* Power up all the PLL's and DLL */
	cx25840_write(client, 0x1, 0x40);

	/* Sys PLL */
	switch (state->id) {
	case V4L2_IDENT_CX23888_AV:
		/*
		 * 50.0 MHz * (0xb + 0xe8ba26/0x2000000)/4 = 5 * 28.636363 MHz
		 * 572.73 MHz before post divide
		 */
		cx25840_write4(client, 0x11c, 0x00e8ba26);
		cx25840_write4(client, 0x118, 0x0000040b);
		break;
	case V4L2_IDENT_CX23887_AV:
		/*
		 * 25.0 MHz * (0x16 + 0x1d1744c/0x2000000)/4 = 5 * 28.636363 MHz
		 * 572.73 MHz before post divide
		 */
		cx25840_write4(client, 0x11c, 0x01d1744c);
		cx25840_write4(client, 0x118, 0x00000416);
		break;
	case V4L2_IDENT_CX23885_AV:
	default:
		/*
		 * 28.636363 MHz * (0x14 + 0x0/0x2000000)/4 = 5 * 28.636363 MHz
		 * 572.73 MHz before post divide
		 */
		cx25840_write4(client, 0x11c, 0x00000000);
		cx25840_write4(client, 0x118, 0x00000414);
		break;
	}

	/* Disable DIF bypass */
	cx25840_write4(client, 0x33c, 0x00000001);

	/* DIF Src phase inc */
	cx25840_write4(client, 0x340, 0x0df7df83);

	/*
	 * Vid PLL
	 * Setup for a BT.656 pixel clock of 13.5 Mpixels/second
	 *
	 * 28.636363 MHz * (0xf + 0x02be2c9/0x2000000)/4 = 8 * 13.5 MHz
	 * 432.0 MHz before post divide
	 */
	cx25840_write4(client, 0x10c, 0x002be2c9);
	cx25840_write4(client, 0x108, 0x0000040f);

	/* Luma */
	cx25840_write4(client, 0x414, 0x00107d12);

	/* Chroma */
	cx25840_write4(client, 0x420, 0x3d008282);

	/*
	 * Aux PLL
	 * Initial setup for audio sample clock:
	 * 48 ksps, 16 bits/sample, x160 multiplier = 122.88 MHz
	 * Intial I2S output/master clock(?):
	 * 48 ksps, 16 bits/sample, x16 multiplier = 12.288 MHz
	 */
	switch (state->id) {
	case V4L2_IDENT_CX23888_AV:
		/*
		 * 50.0 MHz * (0x7 + 0x0bedfa4/0x2000000)/3 = 122.88 MHz
		 * 368.64 MHz before post divide
		 * 122.88 MHz / 0xa = 12.288 MHz
		 */
		cx25840_write4(client, 0x114, 0x00bedfa4);
		cx25840_write4(client, 0x110, 0x000a0307);
		break;
	case V4L2_IDENT_CX23887_AV:
		/*
		 * 25.0 MHz * (0xe + 0x17dbf48/0x2000000)/3 = 122.88 MHz
		 * 368.64 MHz before post divide
		 * 122.88 MHz / 0xa = 12.288 MHz
		 */
		cx25840_write4(client, 0x114, 0x017dbf48);
		cx25840_write4(client, 0x110, 0x000a030e);
		break;
	case V4L2_IDENT_CX23885_AV:
	default:
		/*
		 * 28.636363 MHz * (0xc + 0x1bf0c9e/0x2000000)/3 = 122.88 MHz
		 * 368.64 MHz before post divide
		 * 122.88 MHz / 0xa = 12.288 MHz
		 */
		cx25840_write4(client, 0x114, 0x01bf0c9e);
		cx25840_write4(client, 0x110, 0x000a030c);
		break;
	};

	/* ADC2 input select */
	cx25840_write(client, 0x102, 0x10);

	/* VIN1 & VIN5 */
	cx25840_write(client, 0x103, 0x11);

	/* Enable format auto detect */
	cx25840_write(client, 0x400, 0);
	/* Fast subchroma lock */
	/* White crush, Chroma AGC & Chroma Killer enabled */
	cx25840_write(client, 0x401, 0xe8);

	/* Select AFE clock pad output source */
	cx25840_write(client, 0x144, 0x05);

	/* Drive GPIO2 direction and values for HVR1700
	 * where an onboard mux selects the output of demodulator
	 * vs the 417. Failure to set this results in no DTV.
	 * It's safe to set this across all Hauppauge boards
	 * currently, regardless of the board type.
	 */
	cx25840_write(client, 0x160, 0x1d);
	cx25840_write(client, 0x164, 0x00);

	/* Do the firmware load in a work handler to prevent.
	   Otherwise the kernel is blocked waiting for the
	   bit-banging i2c interface to finish uploading the
	   firmware. */
	INIT_WORK(&state->fw_work, cx25840_work_handler);
	init_waitqueue_head(&state->fw_wait);
	q = create_singlethread_workqueue("cx25840_fw");
	prepare_to_wait(&state->fw_wait, &wait, TASK_UNINTERRUPTIBLE);
	queue_work(q, &state->fw_work);
	schedule();
	finish_wait(&state->fw_wait, &wait);
	destroy_workqueue(q);

	cx25840_std_setup(client);

	/* (re)set input */
	set_input(client, state->vid_input, state->aud_input);

	/* start microcontroller */
	cx25840_and_or(client, 0x803, ~0x10, 0x10);

	/* Disable and clear video interrupts - we don't use them */
	cx25840_write4(client, CX25840_VID_INT_STAT_REG, 0xffffffff);

	/* Disable and clear audio interrupts - we don't use them */
	cx25840_write(client, CX25840_AUD_INT_CTRL_REG, 0xff);
	cx25840_write(client, CX25840_AUD_INT_STAT_REG, 0xff);
}