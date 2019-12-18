#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ head; } ;
struct fw_flowc_wr {TYPE_1__* mnemval; void* flowid_len16; void* op_to_nparams; } ;
struct cxgbi_sock {int tx_chan; int rss_qid; int snd_nxt; int rcv_nxt; int advmss; size_t port_id; TYPE_2__* cdev; int /*<<< orphan*/  tid; } ;
struct TYPE_4__ {int pfvf; int /*<<< orphan*/ * ports; } ;
struct TYPE_3__ {scalar_t__* r4; void* val; scalar_t__ mnemonic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 scalar_t__ FW_FLOWC_MNEM_CH ; 
 scalar_t__ FW_FLOWC_MNEM_IQID ; 
 scalar_t__ FW_FLOWC_MNEM_MSS ; 
 scalar_t__ FW_FLOWC_MNEM_PFNVFN ; 
 scalar_t__ FW_FLOWC_MNEM_PORT ; 
 scalar_t__ FW_FLOWC_MNEM_RCVNXT ; 
 scalar_t__ FW_FLOWC_MNEM_SNDBUF ; 
 scalar_t__ FW_FLOWC_MNEM_SNDNXT ; 
 int /*<<< orphan*/  FW_FLOWC_WR ; 
 int FW_FLOWC_WR_NPARAMS (int) ; 
 int FW_WR_FLOWID (int /*<<< orphan*/ ) ; 
 int FW_WR_LEN16 (int /*<<< orphan*/ ) ; 
 int FW_WR_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_wr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int cxgb4i_snd_win ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  set_queue (struct sk_buff*,int /*<<< orphan*/ ,struct cxgbi_sock*) ; 

__attribute__((used)) static inline void send_tx_flowc_wr(struct cxgbi_sock *csk)
{
	struct sk_buff *skb;
	struct fw_flowc_wr *flowc;
	int flowclen, i;

	flowclen = 80;
	skb = alloc_wr(flowclen, 0, GFP_ATOMIC);
	flowc = (struct fw_flowc_wr *)skb->head;
	flowc->op_to_nparams =
		htonl(FW_WR_OP(FW_FLOWC_WR) | FW_FLOWC_WR_NPARAMS(8));
	flowc->flowid_len16 =
		htonl(FW_WR_LEN16(DIV_ROUND_UP(72, 16)) |
				FW_WR_FLOWID(csk->tid));
	flowc->mnemval[0].mnemonic = FW_FLOWC_MNEM_PFNVFN;
	flowc->mnemval[0].val = htonl(csk->cdev->pfvf);
	flowc->mnemval[1].mnemonic = FW_FLOWC_MNEM_CH;
	flowc->mnemval[1].val = htonl(csk->tx_chan);
	flowc->mnemval[2].mnemonic = FW_FLOWC_MNEM_PORT;
	flowc->mnemval[2].val = htonl(csk->tx_chan);
	flowc->mnemval[3].mnemonic = FW_FLOWC_MNEM_IQID;
	flowc->mnemval[3].val = htonl(csk->rss_qid);
	flowc->mnemval[4].mnemonic = FW_FLOWC_MNEM_SNDNXT;
	flowc->mnemval[4].val = htonl(csk->snd_nxt);
	flowc->mnemval[5].mnemonic = FW_FLOWC_MNEM_RCVNXT;
	flowc->mnemval[5].val = htonl(csk->rcv_nxt);
	flowc->mnemval[6].mnemonic = FW_FLOWC_MNEM_SNDBUF;
	flowc->mnemval[6].val = htonl(cxgb4i_snd_win);
	flowc->mnemval[7].mnemonic = FW_FLOWC_MNEM_MSS;
	flowc->mnemval[7].val = htonl(csk->advmss);
	flowc->mnemval[8].mnemonic = 0;
	flowc->mnemval[8].val = 0;
	for (i = 0; i < 9; i++) {
		flowc->mnemval[i].r4[0] = 0;
		flowc->mnemval[i].r4[1] = 0;
		flowc->mnemval[i].r4[2] = 0;
	}
	set_queue(skb, CPL_PRIORITY_DATA, csk);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p, tid 0x%x, %u,%u,%u,%u,%u,%u,%u.\n",
		csk, csk->tid, 0, csk->tx_chan, csk->rss_qid,
		csk->snd_nxt, csk->rcv_nxt, cxgb4i_snd_win,
		csk->advmss);

	cxgb4_ofld_send(csk->cdev->ports[csk->port_id], skb);
}