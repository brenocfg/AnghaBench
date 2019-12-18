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
struct ps3av_pkt_audio_mode {int /*<<< orphan*/  audio_downmix_level; int /*<<< orphan*/  audio_downmix; int /*<<< orphan*/  audio_layout; scalar_t__ audio_num_of_ch; } ;
struct TYPE_5__ {int /*<<< orphan*/  lsv; int /*<<< orphan*/  dm; } ;
struct TYPE_4__ {scalar_t__ ss; scalar_t__ sf; } ;
struct TYPE_6__ {scalar_t__ ct; scalar_t__ cc; } ;
struct ps3av_audio_info_frame {TYPE_2__ pb5; int /*<<< orphan*/  pb4; scalar_t__ pb3; TYPE_1__ pb2; TYPE_3__ pb1; } ;

/* Variables and functions */

__attribute__((used)) static void ps3av_cnv_info(struct ps3av_audio_info_frame *info,
			   const struct ps3av_pkt_audio_mode *mode)
{
	info->pb1.cc = mode->audio_num_of_ch + 1;	/* CH2:0x01 --- CH8:0x07 */
	info->pb1.ct = 0;
	info->pb2.sf = 0;
	info->pb2.ss = 0;

	info->pb3 = 0;		/* check mode->audio_format ?? */
	info->pb4 = mode->audio_layout;
	info->pb5.dm = mode->audio_downmix;
	info->pb5.lsv = mode->audio_downmix_level;
}