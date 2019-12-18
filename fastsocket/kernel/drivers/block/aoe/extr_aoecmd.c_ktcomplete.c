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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct sk_buff {int dummy; } ;
struct frame {int /*<<< orphan*/  head; TYPE_2__* t; struct sk_buff* r_skb; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct TYPE_7__ {int /*<<< orphan*/  active; } ;
struct TYPE_6__ {TYPE_1__* d; } ;
struct TYPE_5__ {int aoeminor; } ;

/* Variables and functions */
 TYPE_4__* iocq ; 
 int /*<<< orphan*/ * ktiowq ; 
 TYPE_3__* kts ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ncpus ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ktcomplete(struct frame *f, struct sk_buff *skb)
{
	int id;
	ulong flags;

	f->r_skb = skb;
	id = f->t->d->aoeminor % ncpus;
	spin_lock_irqsave(&iocq[id].lock, flags);
	if (!kts[id].active) {
		spin_unlock_irqrestore(&iocq[id].lock, flags);
		/* The thread with id has not been spawned yet,
		 * so delegate the work to the main thread and
		 * try spawning a new thread.
		 */
		id = 0;
		spin_lock_irqsave(&iocq[id].lock, flags);
	}
	list_add_tail(&f->head, &iocq[id].head);
	spin_unlock_irqrestore(&iocq[id].lock, flags);
	wake_up(&ktiowq[id]);
}