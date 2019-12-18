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
struct sk_buff {int dummy; } ;
struct pcbit_dev {int dummy; } ;
struct pcbit_chan {int s_refnum; int /*<<< orphan*/  callref; } ;
struct callb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAUSE_NORMAL ; 
 int /*<<< orphan*/  MSG_DISC_REQ ; 
 int capi_disc_req (int /*<<< orphan*/ ,struct sk_buff**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_ref_num ; 
 int /*<<< orphan*/  pcbit_l2_write (struct pcbit_dev*,int /*<<< orphan*/ ,int,struct sk_buff*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

void cb_disc_2(struct pcbit_dev * dev, struct pcbit_chan* chan, 
	       struct callb_data *data)
{
 	struct sk_buff *skb;
	int len;
        ushort refnum;

        if ((len = capi_disc_req(chan->callref, &skb, CAUSE_NORMAL)) < 0)
        {
                printk("capi_disc_req failed\n");
                return;
        }

        refnum = last_ref_num++ & 0x7fffU;
        chan->s_refnum = refnum;

        pcbit_l2_write(dev, MSG_DISC_REQ, refnum, skb, len);  
}