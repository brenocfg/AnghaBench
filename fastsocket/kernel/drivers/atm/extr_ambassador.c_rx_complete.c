#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct TYPE_12__ {size_t max_sdu; } ;
struct TYPE_13__ {TYPE_1__ rxtp; } ;
struct atm_vcc {TYPE_3__* stats; int /*<<< orphan*/  (* push ) (struct atm_vcc*,struct sk_buff*) ;TYPE_2__ qos; } ;
struct TYPE_17__ {int /*<<< orphan*/  length; int /*<<< orphan*/  status; int /*<<< orphan*/  vc; int /*<<< orphan*/  handle; } ;
typedef  TYPE_6__ rx_out ;
struct TYPE_15__ {int /*<<< orphan*/  unused; int /*<<< orphan*/  aborted; int /*<<< orphan*/  toolong; int /*<<< orphan*/  badcrc; int /*<<< orphan*/  error; int /*<<< orphan*/  ok; } ;
struct TYPE_16__ {TYPE_4__ rx; } ;
struct TYPE_18__ {TYPE_5__ stats; struct atm_vcc** rxer; } ;
typedef  TYPE_7__ amb_dev ;
struct TYPE_14__ {int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  rx; } ;
struct TYPE_11__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 size_t ABORT_ERR ; 
 TYPE_10__* ATM_SKB (struct sk_buff*) ; 
 size_t CRC_ERR ; 
 int DBG_FLOW ; 
 int DBG_INFO ; 
 int DBG_RX ; 
 int DBG_WARN ; 
 int /*<<< orphan*/  KERN_INFO ; 
 size_t LEN_ERR ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*) ; 
 size_t UNUSED_ERR ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 scalar_t__ atm_charge (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* bus_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dump_skb (char*,size_t,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void rx_complete (amb_dev * dev, rx_out * rx) {
  struct sk_buff * skb = bus_to_virt (rx->handle);
  u16 vc = be16_to_cpu (rx->vc);
  // unused: u16 lec_id = be16_to_cpu (rx->lec_id);
  u16 status = be16_to_cpu (rx->status);
  u16 rx_len = be16_to_cpu (rx->length);
  
  PRINTD (DBG_FLOW|DBG_RX, "rx_complete %p %p (len=%hu)", dev, rx, rx_len);
  
  // XXX move this in and add to VC stats ???
  if (!status) {
    struct atm_vcc * atm_vcc = dev->rxer[vc];
    dev->stats.rx.ok++;
    
    if (atm_vcc) {
      
      if (rx_len <= atm_vcc->qos.rxtp.max_sdu) {
	
	if (atm_charge (atm_vcc, skb->truesize)) {
	  
	  // prepare socket buffer
	  ATM_SKB(skb)->vcc = atm_vcc;
	  skb_put (skb, rx_len);
	  
	  dump_skb ("<<<", vc, skb);
	  
	  // VC layer stats
	  atomic_inc(&atm_vcc->stats->rx);
	  __net_timestamp(skb);
	  // end of our responsability
	  atm_vcc->push (atm_vcc, skb);
	  return;
	  
	} else {
	  // someone fix this (message), please!
	  PRINTD (DBG_INFO|DBG_RX, "dropped thanks to atm_charge (vc %hu, truesize %u)", vc, skb->truesize);
	  // drop stats incremented in atm_charge
	}
	
      } else {
      	PRINTK (KERN_INFO, "dropped over-size frame");
	// should we count this?
	atomic_inc(&atm_vcc->stats->rx_drop);
      }
      
    } else {
      PRINTD (DBG_WARN|DBG_RX, "got frame but RX closed for channel %hu", vc);
      // this is an adapter bug, only in new version of microcode
    }
    
  } else {
    dev->stats.rx.error++;
    if (status & CRC_ERR)
      dev->stats.rx.badcrc++;
    if (status & LEN_ERR)
      dev->stats.rx.toolong++;
    if (status & ABORT_ERR)
      dev->stats.rx.aborted++;
    if (status & UNUSED_ERR)
      dev->stats.rx.unused++;
  }
  
  dev_kfree_skb_any (skb);
  return;
}