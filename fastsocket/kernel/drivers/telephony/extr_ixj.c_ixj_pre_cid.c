#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int cidplay; int /*<<< orphan*/  recording; int /*<<< orphan*/  playing; } ;
struct TYPE_13__ {int low; } ;
struct TYPE_15__ {int cid_base_frame_size; TYPE_2__ flags; TYPE_1__ baseframe; int /*<<< orphan*/  aec_level; int /*<<< orphan*/  cid_play_aec_level; int /*<<< orphan*/  cid_rec_flag; int /*<<< orphan*/  cid_rec_volume; int /*<<< orphan*/  rec_codec; int /*<<< orphan*/  cid_rec_codec; int /*<<< orphan*/  cid_play_flag; int /*<<< orphan*/  cid_play_volume; int /*<<< orphan*/  play_frame_size; int /*<<< orphan*/  cid_play_frame_size; int /*<<< orphan*/  play_codec; int /*<<< orphan*/  cid_play_codec; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  LINEAR16 ; 
 int /*<<< orphan*/  get_play_volume (TYPE_3__*) ; 
 int /*<<< orphan*/  get_rec_volume (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_cpt_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_play_start (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_play_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  set_base_frame (TYPE_3__*,int) ; 
 int /*<<< orphan*/  set_play_codec (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_play_volume (TYPE_3__*,int) ; 

__attribute__((used)) static void ixj_pre_cid(IXJ *j)
{
	j->cid_play_codec = j->play_codec;
	j->cid_play_frame_size = j->play_frame_size;
	j->cid_play_volume = get_play_volume(j);
	j->cid_play_flag = j->flags.playing;

	j->cid_rec_codec = j->rec_codec;
	j->cid_rec_volume = get_rec_volume(j);
	j->cid_rec_flag = j->flags.recording;

	j->cid_play_aec_level = j->aec_level;

	switch(j->baseframe.low) {
		case 0xA0:
			j->cid_base_frame_size = 20;
			break;
		case 0x50:
			j->cid_base_frame_size = 10;
			break;
		case 0xF0:
			j->cid_base_frame_size = 30;
			break;
	}

	ixj_play_stop(j);
	ixj_cpt_stop(j);

	j->flags.cidplay = 1;

	set_base_frame(j, 30);
	set_play_codec(j, LINEAR16);
	set_play_volume(j, 0x1B);
	ixj_play_start(j);
}