#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smd_channel {void (* notify ) (void*,unsigned int) ;TYPE_2__* send; TYPE_1__* recv; int /*<<< orphan*/  ch_list; void* priv; int /*<<< orphan*/  last_state; scalar_t__ current_packet; } ;
typedef  struct smd_channel smd_channel_t ;
struct TYPE_4__ {scalar_t__ head; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SMD_SS_CLOSED ; 
 scalar_t__ SMD_SS_CLOSING ; 
 int /*<<< orphan*/  SMD_SS_OPENED ; 
 int /*<<< orphan*/  SMD_SS_OPENING ; 
 void do_nothing_notify (void*,unsigned int) ; 
 int /*<<< orphan*/  hc_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smd_ch_list ; 
 struct smd_channel* smd_get_channel (char const*) ; 
 scalar_t__ smd_initialized ; 
 int /*<<< orphan*/  smd_kick (struct smd_channel*) ; 
 int /*<<< orphan*/  smd_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int smd_open(const char *name, smd_channel_t **_ch,
	     void *priv, void (*notify)(void *, unsigned))
{
	struct smd_channel *ch;
	unsigned long flags;

	if (smd_initialized == 0) {
		pr_info("smd_open() before smd_init()\n");
		return -ENODEV;
	}

	ch = smd_get_channel(name);
	if (!ch)
		return -ENODEV;

	if (notify == 0)
		notify = do_nothing_notify;

	ch->notify = notify;
	ch->current_packet = 0;
	ch->last_state = SMD_SS_CLOSED;
	ch->priv = priv;

	*_ch = ch;

	spin_lock_irqsave(&smd_lock, flags);
	list_add(&ch->ch_list, &smd_ch_list);

	/* If the remote side is CLOSING, we need to get it to
	 * move to OPENING (which we'll do by moving from CLOSED to
	 * OPENING) and then get it to move from OPENING to
	 * OPENED (by doing the same state change ourselves).
	 *
	 * Otherwise, it should be OPENING and we can move directly
	 * to OPENED so that it will follow.
	 */
	if (ch->recv->state == SMD_SS_CLOSING) {
		ch->send->head = 0;
		hc_set_state(ch->send, SMD_SS_OPENING);
	} else {
		hc_set_state(ch->send, SMD_SS_OPENED);
	}
	spin_unlock_irqrestore(&smd_lock, flags);
	smd_kick(ch);

	return 0;
}