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
typedef  void* ushort ;
struct sk_buff {int dummy; } ;
struct pcbit_dev {TYPE_1__* dev_if; int /*<<< orphan*/  id; } ;
struct pcbit_chan {void* s_refnum; int /*<<< orphan*/  id; } ;
struct callb_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_2__ isdn_ctrl ;
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_DCONN ; 
 int /*<<< orphan*/  MSG_CONN_ACTV_RESP ; 
 int /*<<< orphan*/  MSG_SELP_REQ ; 
 int capi_conn_active_resp (struct pcbit_chan*,struct sk_buff**) ; 
 int capi_select_proto_req (struct pcbit_chan*,struct sk_buff**,int) ; 
 int /*<<< orphan*/  last_ref_num ; 
 int /*<<< orphan*/  pcbit_l2_write (struct pcbit_dev*,int /*<<< orphan*/ ,void*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void cb_out_2(struct pcbit_dev * dev, struct pcbit_chan* chan, 
	      struct callb_data *data) 
{
        isdn_ctrl ictl;
 	struct sk_buff *skb;
	int len;
        ushort refnum;

        if ((len=capi_conn_active_resp(chan, &skb)) < 0)
        {
                printk("capi_conn_active_req failed\n");
                return;
        }

        refnum = last_ref_num++ & 0x7fffU;
        chan->s_refnum = refnum;

        pcbit_l2_write(dev, MSG_CONN_ACTV_RESP, refnum, skb, len);


        ictl.command = ISDN_STAT_DCONN;
        ictl.driver=dev->id;
        ictl.arg=chan->id;
        dev->dev_if->statcallb(&ictl);

        /* ACTIVE D-channel */

        /* Select protocol  */

        if ((len=capi_select_proto_req(chan, &skb, 1 /*outgoing*/)) < 0) { 
                printk("capi_select_proto_req failed\n");
                return;
        }

        refnum = last_ref_num++ & 0x7fffU;
        chan->s_refnum = refnum;

        pcbit_l2_write(dev, MSG_SELP_REQ, refnum, skb, len);
}