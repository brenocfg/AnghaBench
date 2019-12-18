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
typedef  TYPE_1__* pdabusb_t ;
struct TYPE_3__ {scalar_t__ got_mem; int /*<<< orphan*/  lock; int /*<<< orphan*/  rec_buff_list; int /*<<< orphan*/  free_buff_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dabusb_free_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dabusb_free_buffers (pdabusb_t s)
{
	unsigned long flags;
	dbg("dabusb_free_buffers");

	spin_lock_irqsave(&s->lock, flags);

	dabusb_free_queue (&s->free_buff_list);
	dabusb_free_queue (&s->rec_buff_list);

	spin_unlock_irqrestore(&s->lock, flags);

	s->got_mem = 0;
	return 0;
}