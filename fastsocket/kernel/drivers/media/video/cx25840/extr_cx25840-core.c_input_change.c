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
typedef  int v4l2_std_id ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; int pvr150_workaround; scalar_t__ radio; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_M_JP ; 
 int V4L2_STD_NTSC_M_KR ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ is_cx2583x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_change(struct i2c_client *client)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	v4l2_std_id std = state->std;

	/* Follow step 8c and 8d of section 3.16 in the cx25840 datasheet */
	if (std & V4L2_STD_SECAM) {
		cx25840_write(client, 0x402, 0);
	}
	else {
		cx25840_write(client, 0x402, 0x04);
		cx25840_write(client, 0x49f, (std & V4L2_STD_NTSC) ? 0x14 : 0x11);
	}
	cx25840_and_or(client, 0x401, ~0x60, 0);
	cx25840_and_or(client, 0x401, ~0x60, 0x60);

	/* Don't write into audio registers on cx2583x chips */
	if (is_cx2583x(state))
		return;

	cx25840_and_or(client, 0x810, ~0x01, 1);

	if (state->radio) {
		cx25840_write(client, 0x808, 0xf9);
		cx25840_write(client, 0x80b, 0x00);
	}
	else if (std & V4L2_STD_525_60) {
		/* Certain Hauppauge PVR150 models have a hardware bug
		   that causes audio to drop out. For these models the
		   audio standard must be set explicitly.
		   To be precise: it affects cards with tuner models
		   85, 99 and 112 (model numbers from tveeprom). */
		int hw_fix = state->pvr150_workaround;

		if (std == V4L2_STD_NTSC_M_JP) {
			/* Japan uses EIAJ audio standard */
			cx25840_write(client, 0x808, hw_fix ? 0x2f : 0xf7);
		} else if (std == V4L2_STD_NTSC_M_KR) {
			/* South Korea uses A2 audio standard */
			cx25840_write(client, 0x808, hw_fix ? 0x3f : 0xf8);
		} else {
			/* Others use the BTSC audio standard */
			cx25840_write(client, 0x808, hw_fix ? 0x1f : 0xf6);
		}
		cx25840_write(client, 0x80b, 0x00);
	} else if (std & V4L2_STD_PAL) {
		/* Autodetect audio standard and audio system */
		cx25840_write(client, 0x808, 0xff);
		/* Since system PAL-L is pretty much non-existant and
		   not used by any public broadcast network, force
		   6.5 MHz carrier to be interpreted as System DK,
		   this avoids DK audio detection instability */
	       cx25840_write(client, 0x80b, 0x00);
	} else if (std & V4L2_STD_SECAM) {
		/* Autodetect audio standard and audio system */
		cx25840_write(client, 0x808, 0xff);
		/* If only one of SECAM-DK / SECAM-L is required, then force
		  6.5MHz carrier, else autodetect it */
		if ((std & V4L2_STD_SECAM_DK) &&
		    !(std & (V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC))) {
			/* 6.5 MHz carrier to be interpreted as System DK */
			cx25840_write(client, 0x80b, 0x00);
	       } else if (!(std & V4L2_STD_SECAM_DK) &&
			  (std & (V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC))) {
			/* 6.5 MHz carrier to be interpreted as System L */
			cx25840_write(client, 0x80b, 0x08);
	       } else {
			/* 6.5 MHz carrier to be autodetected */
			cx25840_write(client, 0x80b, 0x10);
	       }
	}

	cx25840_and_or(client, 0x810, ~0x01, 0);
}