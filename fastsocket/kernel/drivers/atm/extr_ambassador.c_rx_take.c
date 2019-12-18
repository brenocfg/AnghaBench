#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  start; TYPE_6__* ptr; } ;
struct TYPE_11__ {scalar_t__ pending; scalar_t__ low; int /*<<< orphan*/  lock; int /*<<< orphan*/  emptied; scalar_t__ buffers_wanted; TYPE_1__ out; } ;
typedef  TYPE_2__ amb_rxq ;
struct TYPE_12__ {TYPE_2__* rxq; } ;
typedef  TYPE_3__ amb_dev ;
struct TYPE_13__ {scalar_t__ length; scalar_t__ status; } ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_RX ; 
 TYPE_6__* NEXTQ (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTD (int,char*,TYPE_3__*,unsigned char) ; 
 int /*<<< orphan*/  rx_complete (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rx_take (amb_dev * dev, unsigned char pool) {
  amb_rxq * rxq = &dev->rxq[pool];
  unsigned long flags;
  
  PRINTD (DBG_FLOW|DBG_RX, "rx_take %p[%hu]", dev, pool);
  
  spin_lock_irqsave (&rxq->lock, flags);
  
  if (rxq->pending && (rxq->out.ptr->status || rxq->out.ptr->length)) {
    // deal with RX completion
    rx_complete (dev, rxq->out.ptr);
    // mark unused again
    rxq->out.ptr->status = 0;
    rxq->out.ptr->length = 0;
    // remove item
    rxq->pending--;
    rxq->out.ptr = NEXTQ (rxq->out.ptr, rxq->out.start, rxq->out.limit);
    
    if (rxq->pending < rxq->low)
      rxq->low = rxq->pending;
    spin_unlock_irqrestore (&rxq->lock, flags);
    return 0;
  } else {
    if (!rxq->pending && rxq->buffers_wanted)
      rxq->emptied++;
    spin_unlock_irqrestore (&rxq->lock, flags);
    return -1;
  }
}