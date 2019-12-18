#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int playing; int play_first_frame; scalar_t__ recording; } ;
struct TYPE_8__ {int low; } ;
struct TYPE_10__ {int play_codec; int play_mode; int play_frame_size; int write_buffers_empty; int write_buffer_size; int /*<<< orphan*/  aec_level; TYPE_2__ flags; TYPE_1__ ver; scalar_t__ write_buffer; scalar_t__ write_buffer_wp; scalar_t__ write_buffer_rp; scalar_t__ write_buffer_end; int /*<<< orphan*/  board; scalar_t__ drybuffer; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 int ENOMEM ; 
#define  G723_53 135 
#define  G723_63 134 
#define  G728 133 
#define  G729 132 
#define  G729B 131 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  TS41 130 
#define  TS48 129 
#define  TS85 128 
 scalar_t__ ixj_WriteDSPCommand (int,TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_aec_start (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_play_stop (TYPE_3__*) ; 
 int ixjdebug ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int ixj_play_start(IXJ *j)
{
	unsigned short cmd = 0x0000;

	if (j->write_buffer) {
		ixj_play_stop(j);
	}

	if(ixjdebug & 0x0002)
		printk("IXJ %d Starting Play Codec %d at %ld\n", j->board, j->play_codec, jiffies);

	j->flags.playing = 1;
	ixj_WriteDSPCommand(0x0FE0, j);	/* Put the DSP in full power mode. */

	j->flags.play_first_frame = 1;
	j->drybuffer = 0;

	if (!j->play_mode) {
		switch (j->play_codec) {
		case G723_63:
			cmd = 0x5231;
			break;
		case G723_53:
			cmd = 0x5232;
			break;
		case TS85:
			cmd = 0x5230;	/* TrueSpeech 8.5 */

			break;
		case TS48:
			cmd = 0x5233;	/* TrueSpeech 4.8 */

			break;
		case TS41:
			cmd = 0x5234;	/* TrueSpeech 4.1 */

			break;
		case G728:
			cmd = 0x5235;
			break;
		case G729:
		case G729B:
			cmd = 0x5236;
			break;
		default:
			return 1;
		}
		if (ixj_WriteDSPCommand(cmd, j))
			return -1;
	}
	j->write_buffer = kmalloc(j->play_frame_size * 2, GFP_ATOMIC);
	if (!j->write_buffer) {
		printk("Write buffer allocation for ixj board %d failed!\n", j->board);
		return -ENOMEM;
	}
/*	j->write_buffers_empty = 2; */
	j->write_buffers_empty = 1; 
	j->write_buffer_size = j->play_frame_size * 2;
	j->write_buffer_end = j->write_buffer + j->play_frame_size * 2;
	j->write_buffer_rp = j->write_buffer_wp = j->write_buffer;

	if (ixj_WriteDSPCommand(0x5202, j))		/* Set Poll sync mode */

		return -1;

	switch (j->play_mode) {
	case 0:
		cmd = 0x2C03;
		break;
	case 2:
		if (j->ver.low == 0x12) {
			cmd = 0x2C23;
		} else {
			cmd = 0x2C21;
		}
		break;
	case 4:
		if (j->ver.low == 0x12) {
			cmd = 0x2C43;
		} else {
			cmd = 0x2C41;
		}
		break;
	case 5:
		if (j->ver.low == 0x12) {
			cmd = 0x2C53;
		} else {
			cmd = 0x2C51;
		}
		break;
	case 6:
		if (j->ver.low == 0x12) {
			cmd = 0x2C63;
		} else {
			cmd = 0x2C61;
		}
		break;
	}
	if (ixj_WriteDSPCommand(cmd, j))
		return -1;

	if (ixj_WriteDSPCommand(0x2000, j))		/* Playback C2 */
		return -1;

	if (ixj_WriteDSPCommand(0x2000 + j->play_frame_size, j))	/* Playback C3 */
		return -1;

	if (j->flags.recording) {
		ixj_aec_start(j, j->aec_level);
	}

	return 0;
}