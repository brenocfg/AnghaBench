#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_14__ {scalar_t__ traffic_class; size_t max_sdu; } ;
struct TYPE_15__ {TYPE_1__ rxtp; } ;
struct atm_vcc {TYPE_2__ qos; } ;
struct TYPE_16__ {size_t rx_bytes; int /*<<< orphan*/  flags; int /*<<< orphan*/  rx_addr; int /*<<< orphan*/  rx_channel; struct sk_buff* rx_skb; struct atm_vcc** rxer; } ;
typedef  TYPE_3__ hrz_dev ;
struct TYPE_13__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 scalar_t__ ATM_NONE ; 
 TYPE_12__* ATM_SKB (struct sk_buff*) ; 
 int DBG_ERR ; 
 int DBG_FLOW ; 
 int DBG_RX ; 
 int DBG_SKB ; 
 int DBG_VCC ; 
 int DBG_WARN ; 
 int /*<<< orphan*/  FLUSH_RX_CHANNEL (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int RX_COMPLETE_FRAME ; 
 int RX_CRC_32_OK ; 
 int /*<<< orphan*/  SELECT_RX_CHANNEL (TYPE_3__*,size_t) ; 
 int SIMONS_DODGEY_MARKER ; 
 int /*<<< orphan*/  WAIT_FLUSH_RX_COMPLETE (TYPE_3__*) ; 
 int /*<<< orphan*/  YELLOW_LED_OFF (TYPE_3__*) ; 
 int /*<<< orphan*/  YELLOW_LED_ON (TYPE_3__*) ; 
 struct sk_buff* atm_alloc_charge (struct atm_vcc*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_busy ; 
 size_t rx_q_entry_to_length (int) ; 
 size_t rx_q_entry_to_rx_channel (int) ; 
 int rx_queue_entry_next (TYPE_3__*) ; 
 int /*<<< orphan*/  rx_schedule (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rx_data_av_handler (hrz_dev * dev) {
  u32 rx_queue_entry;
  u32 rx_queue_entry_flags;
  u16 rx_len;
  u16 rx_channel;
  
  PRINTD (DBG_FLOW, "hrz_data_av_handler");
  
  // try to grab rx lock (not possible during RX bus mastering)
  if (test_and_set_bit (rx_busy, &dev->flags)) {
    PRINTD (DBG_RX, "locked out of rx lock");
    return;
  }
  PRINTD (DBG_RX, "set rx_busy for dev %p", dev);
  // lock is cleared if we fail now, o/w after bus master completion
  
  YELLOW_LED_OFF(dev);
  
  rx_queue_entry = rx_queue_entry_next (dev);
  
  rx_len = rx_q_entry_to_length (rx_queue_entry);
  rx_channel = rx_q_entry_to_rx_channel (rx_queue_entry);
  
  WAIT_FLUSH_RX_COMPLETE (dev);
  
  SELECT_RX_CHANNEL (dev, rx_channel);
  
  PRINTD (DBG_RX, "rx_queue_entry is: %#x", rx_queue_entry);
  rx_queue_entry_flags = rx_queue_entry & (RX_CRC_32_OK|RX_COMPLETE_FRAME|SIMONS_DODGEY_MARKER);
  
  if (!rx_len) {
    // (at least) bus-mastering breaks if we try to handle a
    // zero-length frame, besides AAL5 does not support them
    PRINTK (KERN_ERR, "zero-length frame!");
    rx_queue_entry_flags &= ~RX_COMPLETE_FRAME;
  }
  
  if (rx_queue_entry_flags & SIMONS_DODGEY_MARKER) {
    PRINTD (DBG_RX|DBG_ERR, "Simon's marker detected!");
  }
  if (rx_queue_entry_flags == (RX_CRC_32_OK | RX_COMPLETE_FRAME)) {
    struct atm_vcc * atm_vcc;
    
    PRINTD (DBG_RX, "got a frame on rx_channel %x len %u", rx_channel, rx_len);
    
    atm_vcc = dev->rxer[rx_channel];
    // if no vcc is assigned to this channel, we should drop the frame
    // (is this what SIMONS etc. was trying to achieve?)
    
    if (atm_vcc) {
      
      if (atm_vcc->qos.rxtp.traffic_class != ATM_NONE) {
	
	if (rx_len <= atm_vcc->qos.rxtp.max_sdu) {
	    
	  struct sk_buff * skb = atm_alloc_charge (atm_vcc, rx_len, GFP_ATOMIC);
	  if (skb) {
	    // remember this so we can push it later
	    dev->rx_skb = skb;
	    // remember this so we can flush it later
	    dev->rx_channel = rx_channel;
	    
	    // prepare socket buffer
	    skb_put (skb, rx_len);
	    ATM_SKB(skb)->vcc = atm_vcc;
	    
	    // simple transfer
	    // dev->rx_regions = 0;
	    // dev->rx_iovec = 0;
	    dev->rx_bytes = rx_len;
	    dev->rx_addr = skb->data;
	    PRINTD (DBG_RX, "RX start simple transfer (addr %p, len %d)",
		    skb->data, rx_len);
	    
	    // do the business
	    rx_schedule (dev, 0);
	    return;
	    
	  } else {
	    PRINTD (DBG_SKB|DBG_WARN, "failed to get skb");
	  }
	  
	} else {
	  PRINTK (KERN_INFO, "frame received on TX-only VC %x", rx_channel);
	  // do we count this?
	}
	
      } else {
	PRINTK (KERN_WARNING, "dropped over-size frame");
	// do we count this?
      }
      
    } else {
      PRINTD (DBG_WARN|DBG_VCC|DBG_RX, "no VCC for this frame (VC closed)");
      // do we count this?
    }
    
  } else {
    // Wait update complete ? SPONG
  }
  
  // RX was aborted
  YELLOW_LED_ON(dev);
  
  FLUSH_RX_CHANNEL (dev,rx_channel);
  clear_bit (rx_busy, &dev->flags);
  
  return;
}