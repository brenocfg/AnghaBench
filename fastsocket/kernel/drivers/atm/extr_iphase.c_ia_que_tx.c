#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ia_vcc {int dummy; } ;
struct atm_vcc {int /*<<< orphan*/  vci; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {struct atm_vcc* vcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_backlog; } ;
typedef  TYPE_1__ IADEV ;

/* Variables and functions */
 TYPE_4__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 struct ia_vcc* INPH_IA_VCC (struct atm_vcc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int ia_avail_descs (TYPE_1__*) ; 
 scalar_t__ ia_pkt_tx (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ia_que_tx (IADEV *iadev) { 
   struct sk_buff *skb;
   int num_desc;
   struct atm_vcc *vcc;
   struct ia_vcc *iavcc;
   num_desc = ia_avail_descs(iadev);

   while (num_desc && (skb = skb_dequeue(&iadev->tx_backlog))) {
      if (!(vcc = ATM_SKB(skb)->vcc)) {
         dev_kfree_skb_any(skb);
         printk("ia_que_tx: Null vcc\n");
         break;
      }
      if (!test_bit(ATM_VF_READY,&vcc->flags)) {
         dev_kfree_skb_any(skb);
         printk("Free the SKB on closed vci %d \n", vcc->vci);
         break;
      }
      iavcc = INPH_IA_VCC(vcc);
      if (ia_pkt_tx (vcc, skb)) {
         skb_queue_head(&iadev->tx_backlog, skb);
      }
      num_desc--;
   }
   return 0;
}