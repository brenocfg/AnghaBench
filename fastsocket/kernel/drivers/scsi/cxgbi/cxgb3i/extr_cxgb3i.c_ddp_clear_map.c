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
struct ulp_mem_io {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct cxgbi_hba {struct cxgbi_device* cdev; } ;
struct cxgbi_device {int /*<<< orphan*/  lldev; struct cxgbi_ddp_info* ddp; } ;
struct cxgbi_ddp_info {unsigned int llimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_CONTROL ; 
 int CXGBI_DBG_DDP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PPOD_SIZE ; 
 unsigned int PPOD_SIZE_SHIFT ; 
 struct sk_buff* alloc_wr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb3_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  ulp_mem_io_set_hdr (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void ddp_clear_map(struct cxgbi_hba *chba, unsigned int tag,
			  unsigned int idx, unsigned int npods)
{
	struct cxgbi_device *cdev = chba->cdev;
	struct cxgbi_ddp_info *ddp = cdev->ddp;
	unsigned int pm_addr = (idx << PPOD_SIZE_SHIFT) + ddp->llimit;
	int i;

	log_debug(1 << CXGBI_DBG_DDP,
		"cdev 0x%p, idx %u, npods %u, tag 0x%x.\n",
		cdev, idx, npods, tag);

	for (i = 0; i < npods; i++, idx++, pm_addr += PPOD_SIZE) {
		struct sk_buff *skb = alloc_wr(sizeof(struct ulp_mem_io) +
						PPOD_SIZE, 0, GFP_ATOMIC);

		if (!skb) {
			pr_err("tag 0x%x, 0x%x, %d/%u, skb OOM.\n",
				tag, idx, i, npods);
			continue;
		}
		ulp_mem_io_set_hdr(skb, pm_addr);
		skb->priority = CPL_PRIORITY_CONTROL;
		cxgb3_ofld_send(cdev->lldev, skb);
	}
}