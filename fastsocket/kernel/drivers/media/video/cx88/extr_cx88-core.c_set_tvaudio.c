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
typedef  int v4l2_std_id ;
struct cx88_core {int tvnorm; void* tvaudio; int /*<<< orphan*/  name; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CX88_VMUX_CABLE ; 
 scalar_t__ CX88_VMUX_TELEVISION ; 
 TYPE_1__ INPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MO_AFECFG_IO ; 
 int V4L2_STD_NTSC_M ; 
 int V4L2_STD_NTSC_M_JP ; 
 int V4L2_STD_PAL_BG ; 
 int V4L2_STD_PAL_DK ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_SECAM_B ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_G ; 
 int V4L2_STD_SECAM_H ; 
 int V4L2_STD_SECAM_L ; 
 void* WW_BG ; 
 void* WW_BTSC ; 
 void* WW_DK ; 
 void* WW_EIAJ ; 
 void* WW_I ; 
 void* WW_L ; 
 void* WW_NONE ; 
 int /*<<< orphan*/  cx88_set_tvaudio (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_start_audio_dma (struct cx88_core*) ; 
 int /*<<< orphan*/  cx_andor (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_norm_to_name (int) ; 

__attribute__((used)) static int set_tvaudio(struct cx88_core *core)
{
	v4l2_std_id norm = core->tvnorm;

	if (CX88_VMUX_TELEVISION != INPUT(core->input).type &&
	    CX88_VMUX_CABLE != INPUT(core->input).type)
		return 0;

	if (V4L2_STD_PAL_BG & norm) {
		core->tvaudio = WW_BG;

	} else if (V4L2_STD_PAL_DK & norm) {
		core->tvaudio = WW_DK;

	} else if (V4L2_STD_PAL_I & norm) {
		core->tvaudio = WW_I;

	} else if (V4L2_STD_SECAM_L & norm) {
		core->tvaudio = WW_L;

	} else if ((V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H) & norm) {
		core->tvaudio = WW_BG;

	} else if (V4L2_STD_SECAM_DK & norm) {
		core->tvaudio = WW_DK;

	} else if ((V4L2_STD_NTSC_M & norm) ||
		   (V4L2_STD_PAL_M  & norm)) {
		core->tvaudio = WW_BTSC;

	} else if (V4L2_STD_NTSC_M_JP & norm) {
		core->tvaudio = WW_EIAJ;

	} else {
		printk("%s/0: tvaudio support needs work for this tv norm [%s], sorry\n",
		       core->name, v4l2_norm_to_name(core->tvnorm));
		core->tvaudio = WW_NONE;
		return 0;
	}

	cx_andor(MO_AFECFG_IO, 0x1f, 0x0);
	cx88_set_tvaudio(core);
	/* cx88_set_stereo(dev,V4L2_TUNER_MODE_STEREO); */

/*
   This should be needed only on cx88-alsa. It seems that some cx88 chips have
   bugs and does require DMA enabled for it to work.
 */
	cx88_start_audio_dma(core);
	return 0;
}