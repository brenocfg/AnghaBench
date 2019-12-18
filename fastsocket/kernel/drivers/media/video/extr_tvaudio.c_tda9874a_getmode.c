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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {TYPE_1__ shadow; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int MAXREGS ; 
 int /*<<< orphan*/  TDA9874A_DSR ; 
 int /*<<< orphan*/  TDA9874A_NECR ; 
 int /*<<< orphan*/  TDA9874A_NSR ; 
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 int chip_read2 (struct CHIPSTATE*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ tda9874a_mode ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int,int,int) ; 

__attribute__((used)) static int tda9874a_getmode(struct CHIPSTATE *chip)
{
	struct v4l2_subdev *sd = &chip->sd;
	int dsr,nsr,mode;
	int necr; /* just for debugging */

	mode = V4L2_TUNER_MODE_MONO;

	if(-1 == (dsr = chip_read2(chip,TDA9874A_DSR)))
		return mode;
	if(-1 == (nsr = chip_read2(chip,TDA9874A_NSR)))
		return mode;
	if(-1 == (necr = chip_read2(chip,TDA9874A_NECR)))
		return mode;

	/* need to store dsr/nsr somewhere */
	chip->shadow.bytes[MAXREGS-2] = dsr;
	chip->shadow.bytes[MAXREGS-1] = nsr;

	if(tda9874a_mode) {
		/* Note: DSR.RSSF and DSR.AMSTAT bits are also checked.
		 * If NICAM auto-muting is enabled, DSR.AMSTAT=1 indicates
		 * that sound has (temporarily) switched from NICAM to
		 * mono FM (or AM) on 1st sound carrier due to high NICAM bit
		 * error count. So in fact there is no stereo in this case :-(
		 * But changing the mode to V4L2_TUNER_MODE_MONO would switch
		 * external 4052 multiplexer in audio_hook().
		 */
		if(nsr & 0x02) /* NSR.S/MB=1 */
			mode |= V4L2_TUNER_MODE_STEREO;
		if(nsr & 0x01) /* NSR.D/SB=1 */
			mode |= V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
	} else {
		if(dsr & 0x02) /* DSR.IDSTE=1 */
			mode |= V4L2_TUNER_MODE_STEREO;
		if(dsr & 0x04) /* DSR.IDDUA=1 */
			mode |= V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
	}

	v4l2_dbg(1, debug, sd, "tda9874a_getmode(): DSR=0x%X, NSR=0x%X, NECR=0x%X, return: %d.\n",
		 dsr, nsr, necr, mode);
	return mode;
}