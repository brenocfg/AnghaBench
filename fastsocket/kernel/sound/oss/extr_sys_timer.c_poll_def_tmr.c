#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 unsigned long curr_ticks ; 
 TYPE_1__ def_tmr ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lock ; 
 unsigned long next_event_time ; 
 scalar_t__ opened ; 
 int /*<<< orphan*/  sequencer_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long ticks_offs ; 
 unsigned long tmr2ticks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmr_ctr ; 
 scalar_t__ tmr_running ; 

__attribute__((used)) static void
poll_def_tmr(unsigned long dummy)
{

	if (opened)
	  {

		  {
			  def_tmr.expires = (1) + jiffies;
			  add_timer(&def_tmr);
		  };

		  if (tmr_running)
		    {
				spin_lock(&lock);
			    tmr_ctr++;
			    curr_ticks = ticks_offs + tmr2ticks(tmr_ctr);

			    if (curr_ticks >= next_event_time)
			      {
				      next_event_time = (unsigned long) -1;
				      sequencer_timer(0);
			      }
				spin_unlock(&lock);
		    }
	  }
}