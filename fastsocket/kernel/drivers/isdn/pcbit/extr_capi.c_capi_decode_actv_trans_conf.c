#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ushort ;
struct sk_buff {scalar_t__* data; } ;
struct pcbit_chan {scalar_t__ layer2link; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

int capi_decode_actv_trans_conf(struct pcbit_chan *chan, struct sk_buff *skb)
{
        ushort errcode;

        if (chan->layer2link != *(skb->data) )
                printk("capi_decode_actv_trans_conf: layer2link doesn't match\n");

        skb_pull(skb, 1);

        errcode = *((ushort*) skb->data);
        skb_pull(skb, 2);

        return errcode;        
}