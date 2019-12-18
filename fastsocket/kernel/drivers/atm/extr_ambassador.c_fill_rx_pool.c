#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned char head; struct sk_buff* data; int /*<<< orphan*/  truesize; TYPE_2__* rxq; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_address; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ rx_in ;
typedef  long gfp_t ;
struct TYPE_5__ {scalar_t__ pending; scalar_t__ maximum; scalar_t__ buffers_wanted; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_2__ amb_rxq ;
typedef  struct sk_buff amb_dev ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_POOL ; 
 int DBG_SKB ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,long) ; 
 scalar_t__ check_area (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dead ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ rx_give (struct sk_buff*,TYPE_1__*,unsigned char) ; 
 unsigned char skb_end_pointer (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_bus (struct sk_buff*) ; 

__attribute__((used)) static void fill_rx_pool (amb_dev * dev, unsigned char pool,
                                 gfp_t priority)
{
  rx_in rx;
  amb_rxq * rxq;
  
  PRINTD (DBG_FLOW|DBG_POOL, "fill_rx_pool %p %hu %x", dev, pool, priority);
  
  if (test_bit (dead, &dev->flags))
    return;
  
  rxq = &dev->rxq[pool];
  while (rxq->pending < rxq->maximum && rxq->pending < rxq->buffers_wanted) {
    
    struct sk_buff * skb = alloc_skb (rxq->buffer_size, priority);
    if (!skb) {
      PRINTD (DBG_SKB|DBG_POOL, "failed to allocate skb for RX pool %hu", pool);
      return;
    }
    if (check_area (skb->data, skb->truesize)) {
      dev_kfree_skb_any (skb);
      return;
    }
    // cast needed as there is no %? for pointer differences
    PRINTD (DBG_SKB, "allocated skb at %p, head %p, area %li",
	    skb, skb->head, (long) (skb_end_pointer(skb) - skb->head));
    rx.handle = virt_to_bus (skb);
    rx.host_address = cpu_to_be32 (virt_to_bus (skb->data));
    if (rx_give (dev, &rx, pool))
      dev_kfree_skb_any (skb);
    
  }
  
  return;
}