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
struct ulptx_idata {int dummy; } ;
struct ulp_mem_io {int dummy; } ;
struct sk_buff {scalar_t__ head; } ;
struct cxgbi_pagepod_hdr {int dummy; } ;
struct cxgbi_pagepod {int dummy; } ;
struct cxgbi_gather_list {int dummy; } ;
struct cxgbi_device {int /*<<< orphan*/ * ports; struct cxgbi_ddp_info* ddp; } ;
struct cxgbi_ddp_info {unsigned int llimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_CONTROL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PPOD_PAGES_MAX ; 
 unsigned int PPOD_SIZE ; 
 struct sk_buff* alloc_wr (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_ddp_ppod_clear (struct cxgbi_pagepod*) ; 
 int /*<<< orphan*/  cxgbi_ddp_ppod_set (struct cxgbi_pagepod*,struct cxgbi_pagepod_hdr*,struct cxgbi_gather_list*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_device*,unsigned int,unsigned int) ; 
 unsigned int roundup (int,int) ; 
 int /*<<< orphan*/  set_queue (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulp_mem_io_set_hdr (struct ulp_mem_io*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ddp_ppod_write_idata(struct cxgbi_device *cdev, unsigned int port_id,
				struct cxgbi_pagepod_hdr *hdr, unsigned int idx,
				unsigned int npods,
				struct cxgbi_gather_list *gl,
				unsigned int gl_pidx)
{
	struct cxgbi_ddp_info *ddp = cdev->ddp;
	struct sk_buff *skb;
	struct ulp_mem_io *req;
	struct ulptx_idata *idata;
	struct cxgbi_pagepod *ppod;
	unsigned int pm_addr = idx * PPOD_SIZE + ddp->llimit;
	unsigned int dlen = PPOD_SIZE * npods;
	unsigned int wr_len = roundup(sizeof(struct ulp_mem_io) +
				sizeof(struct ulptx_idata) + dlen, 16);
	unsigned int i;

	skb = alloc_wr(wr_len, 0, GFP_ATOMIC);
	if (!skb) {
		pr_err("cdev 0x%p, idx %u, npods %u, OOM.\n",
			cdev, idx, npods);
		return -ENOMEM;
	}
	req = (struct ulp_mem_io *)skb->head;
	set_queue(skb, CPL_PRIORITY_CONTROL, NULL);

	ulp_mem_io_set_hdr(req, wr_len, dlen, pm_addr);
	idata = (struct ulptx_idata *)(req + 1);
	ppod = (struct cxgbi_pagepod *)(idata + 1);

	for (i = 0; i < npods; i++, ppod++, gl_pidx += PPOD_PAGES_MAX) {
		if (!hdr && !gl)
			cxgbi_ddp_ppod_clear(ppod);
		else
			cxgbi_ddp_ppod_set(ppod, hdr, gl, gl_pidx);
	}

	cxgb4_ofld_send(cdev->ports[port_id], skb);
	return 0;
}