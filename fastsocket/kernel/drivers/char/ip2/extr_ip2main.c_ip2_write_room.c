#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_6__ {TYPE_1__* driver_data; } ;
struct TYPE_5__ {int Pbuf_stuff; int /*<<< orphan*/  Pbuf_spinlock; } ;
typedef  TYPE_2__* PTTY ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int /*<<< orphan*/  ITRC_WRITE ; 
 int i2OutputFree (TYPE_1__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
ip2_write_room ( PTTY tty )
{
	int bytesFree;
	i2ChanStrPtr  pCh = tty->driver_data;
	unsigned long flags;

	read_lock_irqsave(&pCh->Pbuf_spinlock, flags);
	bytesFree = i2OutputFree( pCh ) - pCh->Pbuf_stuff;
	read_unlock_irqrestore(&pCh->Pbuf_spinlock, flags);

	ip2trace (CHANN, ITRC_WRITE, 11, 1, bytesFree );

	return ((bytesFree > 0) ? bytesFree : 0);
}