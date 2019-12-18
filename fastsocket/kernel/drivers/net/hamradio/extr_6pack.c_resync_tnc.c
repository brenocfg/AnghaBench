#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long data; void (* function ) (unsigned long) ;scalar_t__ expires; } ;
struct sixpack {int status; int status1; int led_state; TYPE_4__ resync_t; TYPE_2__* tty; scalar_t__ status2; scalar_t__ rx_count_cooked; scalar_t__ rx_count; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ SIXP_RESYNC_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_4__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char*,int) ; 

__attribute__((used)) static void resync_tnc(unsigned long channel)
{
	struct sixpack *sp = (struct sixpack *) channel;
	static char resync_cmd = 0xe8;

	/* clear any data that might have been received */

	sp->rx_count = 0;
	sp->rx_count_cooked = 0;

	/* reset state machine */

	sp->status = 1;
	sp->status1 = 1;
	sp->status2 = 0;

	/* resync the TNC */

	sp->led_state = 0x60;
	sp->tty->ops->write(sp->tty, &sp->led_state, 1);
	sp->tty->ops->write(sp->tty, &resync_cmd, 1);


	/* Start resync timer again -- the TNC might be still absent */

	del_timer(&sp->resync_t);
	sp->resync_t.data	= (unsigned long) sp;
	sp->resync_t.function	= resync_tnc;
	sp->resync_t.expires	= jiffies + SIXP_RESYNC_TIMEOUT;
	add_timer(&sp->resync_t);
}