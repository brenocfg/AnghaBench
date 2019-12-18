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
struct TYPE_2__ {int /*<<< orphan*/  subdevice; int /*<<< orphan*/  device; int /*<<< orphan*/  card; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_seq_timer {int ppq; int tempo; int /*<<< orphan*/  skew_base; int /*<<< orphan*/  skew; int /*<<< orphan*/  preferred_resolution; TYPE_1__ alsa_id; int /*<<< orphan*/  type; scalar_t__ running; int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKEW_BASE ; 
 int /*<<< orphan*/  SNDRV_SEQ_TIMER_ALSA ; 
 int /*<<< orphan*/  seq_default_timer_card ; 
 int /*<<< orphan*/  seq_default_timer_class ; 
 int /*<<< orphan*/  seq_default_timer_device ; 
 int /*<<< orphan*/  seq_default_timer_resolution ; 
 int /*<<< orphan*/  seq_default_timer_sclass ; 
 int /*<<< orphan*/  seq_default_timer_subdevice ; 
 int /*<<< orphan*/  snd_seq_timer_set_tick_resolution (int /*<<< orphan*/ *,int,int) ; 

void snd_seq_timer_defaults(struct snd_seq_timer * tmr)
{
	/* setup defaults */
	tmr->ppq = 96;		/* 96 PPQ */
	tmr->tempo = 500000;	/* 120 BPM */
	snd_seq_timer_set_tick_resolution(&tmr->tick, tmr->tempo, tmr->ppq);
	tmr->running = 0;

	tmr->type = SNDRV_SEQ_TIMER_ALSA;
	tmr->alsa_id.dev_class = seq_default_timer_class;
	tmr->alsa_id.dev_sclass = seq_default_timer_sclass;
	tmr->alsa_id.card = seq_default_timer_card;
	tmr->alsa_id.device = seq_default_timer_device;
	tmr->alsa_id.subdevice = seq_default_timer_subdevice;
	tmr->preferred_resolution = seq_default_timer_resolution;

	tmr->skew = tmr->skew_base = SKEW_BASE;
}