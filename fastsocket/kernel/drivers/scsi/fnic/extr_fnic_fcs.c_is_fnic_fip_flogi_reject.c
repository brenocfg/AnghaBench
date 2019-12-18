#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct fip_header {scalar_t__ fip_subcode; int /*<<< orphan*/  fip_dl_len; int /*<<< orphan*/  fip_op; } ;
struct fip_encaps {int dummy; } ;
struct fip_desc {size_t fip_dlen; scalar_t__ fip_dtype; } ;
struct fcoe_ctlr {TYPE_1__* sel_fcf; struct fc_lport* lp; } ;
struct fc_lport {int /*<<< orphan*/  host; } ;
struct fc_frame_header {int dummy; } ;
typedef  enum fip_desc_type { ____Placeholder_fip_desc_type } fip_desc_type ;
struct TYPE_2__ {int /*<<< orphan*/  fc_map; int /*<<< orphan*/  vfid; int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_RJT ; 
 size_t FIP_BPW ; 
 scalar_t__ FIP_DT_FLOGI ; 
 scalar_t__ FIP_OP_LS ; 
 scalar_t__ FIP_SC_REP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 

__attribute__((used)) static inline int is_fnic_fip_flogi_reject(struct fcoe_ctlr *fip,
					 struct sk_buff *skb)
{
	struct fc_lport *lport = fip->lp;
	struct fip_header *fiph;
	struct fc_frame_header *fh = NULL;
	struct fip_desc *desc;
	struct fip_encaps *els;
	enum fip_desc_type els_dtype = 0;
	u16 op;
	u8 els_op;
	u8 sub;

	size_t els_len = 0;
	size_t rlen;
	size_t dlen = 0;

	if (skb_linearize(skb))
		return 0;

	if (skb->len < sizeof(*fiph))
		return 0;

	fiph = (struct fip_header *)skb->data;
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	if (op != FIP_OP_LS)
		return 0;

	if (sub != FIP_SC_REP)
		return 0;

	rlen = ntohs(fiph->fip_dl_len) * 4;
	if (rlen + sizeof(*fiph) > skb->len)
		return 0;

	desc = (struct fip_desc *)(fiph + 1);
	dlen = desc->fip_dlen * FIP_BPW;

	if (desc->fip_dtype == FIP_DT_FLOGI) {

		shost_printk(KERN_DEBUG, lport->host,
			  " FIP TYPE FLOGI: fab name:%llx "
			  "vfid:%d map:%x\n",
			  fip->sel_fcf->fabric_name, fip->sel_fcf->vfid,
			  fip->sel_fcf->fc_map);
		if (dlen < sizeof(*els) + sizeof(*fh) + 1)
			return 0;

		els_len = dlen - sizeof(*els);
		els = (struct fip_encaps *)desc;
		fh = (struct fc_frame_header *)(els + 1);
		els_dtype = desc->fip_dtype;

		if (!fh)
			return 0;

		/*
		 * ELS command code, reason and explanation should be = Reject,
		 * unsupported command and insufficient resource
		 */
		els_op = *(u8 *)(fh + 1);
		if (els_op == ELS_LS_RJT) {
			shost_printk(KERN_INFO, lport->host,
				  "Flogi Request Rejected by Switch\n");
			return 1;
		}
		shost_printk(KERN_INFO, lport->host,
				"Flogi Request Accepted by Switch\n");
	}
	return 0;
}