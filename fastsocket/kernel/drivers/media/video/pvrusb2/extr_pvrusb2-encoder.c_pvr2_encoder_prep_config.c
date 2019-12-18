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
typedef  int u32 ;
struct pvr2_hdw {TYPE_1__* hdw_desc; int /*<<< orphan*/  ctl_lock; } ;
struct TYPE_2__ {scalar_t__ flag_has_cx25840; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_MISC ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int pvr2_encoder_vcmd (struct pvr2_hdw*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/  pvr2_encoder_write_words (struct pvr2_hdw*,int,int*,int) ; 

__attribute__((used)) static int pvr2_encoder_prep_config(struct pvr2_hdw *hdw)
{
	int ret = 0;
	int encMisc3Arg = 0;

#if 0
	/* This inexplicable bit happens in the Hauppauge windows
	   driver (for both 24xxx and 29xxx devices).  However I
	   currently see no difference in behavior with or without
	   this stuff.  Leave this here as a note of its existence,
	   but don't use it. */
	LOCK_TAKE(hdw->ctl_lock); do {
		u32 dat[1];
		dat[0] = 0x80000640;
		pvr2_encoder_write_words(hdw,0x01fe,dat,1);
		pvr2_encoder_write_words(hdw,0x023e,dat,1);
	} while(0); LOCK_GIVE(hdw->ctl_lock);
#endif

	/* Mike Isely <isely@pobox.com> 26-Jan-2006 The windows driver
	   sends the following list of ENC_MISC commands (for both
	   24xxx and 29xxx devices).  Meanings are not entirely clear,
	   however without the ENC_MISC(3,1) command then we risk
	   random perpetual video corruption whenever the video input
	   breaks up for a moment (like when switching channels). */


#if 0
	/* This ENC_MISC(5,0) command seems to hurt 29xxx sync
	   performance on channel changes, but is not a problem on
	   24xxx devices. */
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 5,0,0,0);
#endif

	/* This ENC_MISC(3,encMisc3Arg) command is critical - without
	   it there will eventually be video corruption.  Also, the
	   saa7115 case is strange - the Windows driver is passing 1
	   regardless of device type but if we have 1 for saa7115
	   devices the video turns sluggish.  */
	if (hdw->hdw_desc->flag_has_cx25840) {
		encMisc3Arg = 1;
	} else {
		encMisc3Arg = 0;
	}
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 3,
				 encMisc3Arg,0,0);

	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 8,0,0,0);

#if 0
	/* This ENC_MISC(4,1) command is poisonous, so it is commented
	   out.  But I'm leaving it here anyway to document its
	   existence in the Windows driver.  The effect of this
	   command is that apps displaying the stream become sluggish
	   with stuttering video. */
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 4,1,0,0);
#endif

	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 0,3,0,0);
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4,15,0,0,0);

	/* prevent the PTSs from slowly drifting away in the generated
	   MPEG stream */
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC, 2, 4, 1);

	return ret;
}