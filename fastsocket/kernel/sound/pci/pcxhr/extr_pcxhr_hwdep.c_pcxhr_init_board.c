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
struct pcxhr_rmh {int* stat; int* cmd; int cmd_len; } ;
struct pcxhr_mgr {int capture_chips; int playback_chips; int firmware_num; int granularity; int dsp_version; scalar_t__ is_hr_stereo; scalar_t__ mono_capture; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUPPORTED ; 
 int /*<<< orphan*/  CMD_VERSION ; 
 int EINVAL ; 
 int FIELD_SIZE ; 
 int MASK_FIRST_FIELD ; 
 int PCXHR_PLAYBACK_STREAMS ; 
 int hr222_sub_init (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pcxhr_enable_dsp (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int pcxhr_sub_init (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int,int,...) ; 

__attribute__((used)) static int pcxhr_init_board(struct pcxhr_mgr *mgr)
{
	int err;
	struct pcxhr_rmh rmh;
	int card_streams;

	/* calc the number of all streams used */
	if (mgr->mono_capture)
		card_streams = mgr->capture_chips * 2;
	else
		card_streams = mgr->capture_chips;
	card_streams += mgr->playback_chips * PCXHR_PLAYBACK_STREAMS;

	/* enable interrupts */
	pcxhr_enable_dsp(mgr);

	pcxhr_init_rmh(&rmh, CMD_SUPPORTED);
	err = pcxhr_send_msg(mgr, &rmh);
	if (err)
		return err;
	/* test 8 or 12 phys out */
	if ((rmh.stat[0] & MASK_FIRST_FIELD) != mgr->playback_chips * 2)
		return -EINVAL;
	/* test 8 or 2 phys in */
	if (((rmh.stat[0] >> (2 * FIELD_SIZE)) & MASK_FIRST_FIELD) <
	    mgr->capture_chips * 2)
		return -EINVAL;
	/* test max nb substream per board */
	if ((rmh.stat[1] & 0x5F) < card_streams)
		return -EINVAL;
	/* test max nb substream per pipe */
	if (((rmh.stat[1] >> 7) & 0x5F) < PCXHR_PLAYBACK_STREAMS)
		return -EINVAL;
	snd_printdd("supported formats : playback=%x capture=%x\n",
		    rmh.stat[2], rmh.stat[3]);

	pcxhr_init_rmh(&rmh, CMD_VERSION);
	/* firmware num for DSP */
	rmh.cmd[0] |= mgr->firmware_num;
	/* transfer granularity in samples (should be multiple of 48) */
	rmh.cmd[1] = (1<<23) + mgr->granularity;
	rmh.cmd_len = 2;
	err = pcxhr_send_msg(mgr, &rmh);
	if (err)
		return err;
	snd_printdd("PCXHR DSP version is %d.%d.%d\n", (rmh.stat[0]>>16)&0xff,
		    (rmh.stat[0]>>8)&0xff, rmh.stat[0]&0xff);
	mgr->dsp_version = rmh.stat[0];

	if (mgr->is_hr_stereo)
		err = hr222_sub_init(mgr);
	else
		err = pcxhr_sub_init(mgr);
	return err;
}