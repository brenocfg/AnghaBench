#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_5__ {scalar_t__ Ibuf_stuff; scalar_t__ Ibuf_strip; int /*<<< orphan*/  Ibuf_spinlock; int /*<<< orphan*/  throttled; int /*<<< orphan*/ * pTTY; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int /*<<< orphan*/  ITRC_INPUT ; 
 TYPE_1__* container_of (struct work_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2ChanStr ; 
 int /*<<< orphan*/  i2Input (TYPE_1__*) ; 
 int /*<<< orphan*/  i2InputFlush (TYPE_1__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tqueue_input ; 

__attribute__((used)) static void do_input(struct work_struct *work)
{
	i2ChanStrPtr pCh = container_of(work, i2ChanStr, tqueue_input);
	unsigned long flags;

	ip2trace(CHANN, ITRC_INPUT, 21, 0 );

	// Data input
	if ( pCh->pTTY != NULL ) {
		read_lock_irqsave(&pCh->Ibuf_spinlock, flags);
		if (!pCh->throttled && (pCh->Ibuf_stuff != pCh->Ibuf_strip)) {
			read_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
			i2Input( pCh );
		} else
			read_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
	} else {
		ip2trace(CHANN, ITRC_INPUT, 22, 0 );

		i2InputFlush( pCh );
	}
}