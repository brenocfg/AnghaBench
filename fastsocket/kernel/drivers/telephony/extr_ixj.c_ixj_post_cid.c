#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ cidplay; } ;
struct TYPE_16__ {int cidsize; int /*<<< orphan*/  write_q; scalar_t__ cid_play_flag; scalar_t__ cid_rec_flag; int /*<<< orphan*/  cid_rec_volume; int /*<<< orphan*/  cid_rec_codec; int /*<<< orphan*/  cid_play_volume; int /*<<< orphan*/  cid_play_aec_level; int /*<<< orphan*/  cid_play_codec; int /*<<< orphan*/  cid_base_frame_size; scalar_t__ fskdcnt; int /*<<< orphan*/  board; TYPE_1__ flags; } ;
typedef  TYPE_2__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  PLD_SLIC_STATE_STANDBY ; 
 int /*<<< orphan*/  SLIC_SetState (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_aec_start (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_fsk_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_play_start (TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_play_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_record_start (TYPE_2__*) ; 
 int ixjdebug ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_base_frame (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_play_codec (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_play_volume (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rec_codec (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rec_volume (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixj_post_cid(IXJ *j)
{
	ixj_play_stop(j);

	if(j->cidsize > 5000) {
		SLIC_SetState(PLD_SLIC_STATE_STANDBY, j);
	}
	j->flags.cidplay = 0;
	if(ixjdebug & 0x0200) {
		printk("IXJ phone%d Finished Playing CallerID data %ld\n", j->board, jiffies);
	}

	ixj_fsk_free(j);

	j->fskdcnt = 0;
	set_base_frame(j, j->cid_base_frame_size);
	set_play_codec(j, j->cid_play_codec);
	ixj_aec_start(j, j->cid_play_aec_level);
	set_play_volume(j, j->cid_play_volume);

	set_rec_codec(j, j->cid_rec_codec);
	set_rec_volume(j, j->cid_rec_volume);

	if(j->cid_rec_flag)
		ixj_record_start(j);

	if(j->cid_play_flag)
		ixj_play_start(j);

	if(j->cid_play_flag) {
		wake_up_interruptible(&j->write_q);	/* Wake any blocked writers */
	}
}