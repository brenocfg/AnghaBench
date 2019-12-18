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
struct snd_pcxhr {int nb_streams_capt; int nb_streams_play; int /*<<< orphan*/ * playback_stream; int /*<<< orphan*/ * capture_stream; } ;
struct pcxhr_mgr {int dsp_time_last; int granularity; int timer_toggle; int num_cards; unsigned int src_it_dsp; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_taskq; struct snd_pcxhr** chip; int /*<<< orphan*/  dsp_time_err; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PCXHR_DSP_TIME_INVALID ; 
 int PCXHR_DSP_TIME_MASK ; 
 unsigned int PCXHR_FATAL_DSP_ERR ; 
 int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 unsigned int PCXHR_IRQCS_ACTIVE_PCIDB ; 
 unsigned int PCXHR_IRQ_ASYNC ; 
 unsigned int PCXHR_IRQ_MASK ; 
 unsigned int PCXHR_IRQ_TIMER ; 
 int /*<<< orphan*/  PCXHR_OUTPL (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PCXHR_PLX_IRQCS ; 
 int /*<<< orphan*/  PCXHR_PLX_L2PCIDB ; 
 int /*<<< orphan*/  PCXHR_PLX_MBOX4 ; 
 int /*<<< orphan*/  pcxhr_update_timer_pos (struct pcxhr_mgr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

irqreturn_t pcxhr_interrupt(int irq, void *dev_id)
{
	struct pcxhr_mgr *mgr = dev_id;
	unsigned int reg;
	int i, j;
	struct snd_pcxhr *chip;

	spin_lock(&mgr->lock);

	reg = PCXHR_INPL(mgr, PCXHR_PLX_IRQCS);
	if (! (reg & PCXHR_IRQCS_ACTIVE_PCIDB)) {
		spin_unlock(&mgr->lock);
		/* this device did not cause the interrupt */
		return IRQ_NONE;
	}

	/* clear interrupt */
	reg = PCXHR_INPL(mgr, PCXHR_PLX_L2PCIDB);
	PCXHR_OUTPL(mgr, PCXHR_PLX_L2PCIDB, reg);

	/* timer irq occured */
	if (reg & PCXHR_IRQ_TIMER) {
		int timer_toggle = reg & PCXHR_IRQ_TIMER;
		/* is a 24 bit counter */
		int dsp_time_new =
			PCXHR_INPL(mgr, PCXHR_PLX_MBOX4) & PCXHR_DSP_TIME_MASK;
		int dsp_time_diff = dsp_time_new - mgr->dsp_time_last;

		if ((dsp_time_diff < 0) &&
		    (mgr->dsp_time_last != PCXHR_DSP_TIME_INVALID)) {
			snd_printdd("ERROR DSP TIME old(%d) new(%d) -> "
				    "resynchronize all streams\n",
				    mgr->dsp_time_last, dsp_time_new);
			mgr->dsp_time_err++;
		}
#ifdef CONFIG_SND_DEBUG_VERBOSE
		if (dsp_time_diff == 0)
			snd_printdd("ERROR DSP TIME NO DIFF time(%d)\n",
				    dsp_time_new);
		else if (dsp_time_diff >= (2*mgr->granularity))
			snd_printdd("ERROR DSP TIME TOO BIG old(%d) add(%d)\n",
				    mgr->dsp_time_last,
				    dsp_time_new - mgr->dsp_time_last);
		else if (dsp_time_diff % mgr->granularity)
			snd_printdd("ERROR DSP TIME increased by %d\n",
				    dsp_time_diff);
#endif
		mgr->dsp_time_last = dsp_time_new;

		if (timer_toggle == mgr->timer_toggle) {
			snd_printdd("ERROR TIMER TOGGLE\n");
			mgr->dsp_time_err++;
		}
		mgr->timer_toggle = timer_toggle;

		reg &= ~PCXHR_IRQ_TIMER;
		for (i = 0; i < mgr->num_cards; i++) {
			chip = mgr->chip[i];
			for (j = 0; j < chip->nb_streams_capt; j++)
				pcxhr_update_timer_pos(mgr,
						&chip->capture_stream[j],
						dsp_time_diff);
		}
		for (i = 0; i < mgr->num_cards; i++) {
			chip = mgr->chip[i];
			for (j = 0; j < chip->nb_streams_play; j++)
				pcxhr_update_timer_pos(mgr,
						&chip->playback_stream[j],
						dsp_time_diff);
		}
	}
	/* other irq's handled in the tasklet */
	if (reg & PCXHR_IRQ_MASK) {
		if (reg & PCXHR_IRQ_ASYNC) {
			/* as we didn't request any async notifications,
			 * some kind of xrun error will probably occured
			 */
			/* better resynchronize all streams next interrupt : */
			mgr->dsp_time_last = PCXHR_DSP_TIME_INVALID;
		}
		mgr->src_it_dsp = reg;
		tasklet_schedule(&mgr->msg_taskq);
	}
#ifdef CONFIG_SND_DEBUG_VERBOSE
	if (reg & PCXHR_FATAL_DSP_ERR)
		snd_printdd("FATAL DSP ERROR : %x\n", reg);
#endif
	spin_unlock(&mgr->lock);
	return IRQ_HANDLED;	/* this device caused the interrupt */
}