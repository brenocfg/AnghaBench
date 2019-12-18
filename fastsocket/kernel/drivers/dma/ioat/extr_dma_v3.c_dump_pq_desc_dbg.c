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
struct TYPE_3__ {int /*<<< orphan*/  flags; scalar_t__ phys; } ;
struct ioat_ring_ent {TYPE_1__ txd; struct ioat_pq_ext_descriptor* pq_ex; struct ioat_pq_descriptor* pq; } ;
typedef  void ioat_raw_descriptor ;
struct ioat_pq_ext_descriptor {scalar_t__ next; } ;
struct TYPE_4__ {int /*<<< orphan*/  src_cnt; scalar_t__ q_disable; scalar_t__ p_disable; int /*<<< orphan*/  compl_write; int /*<<< orphan*/  int_en; int /*<<< orphan*/  op; } ;
struct ioat_pq_descriptor {int /*<<< orphan*/  q_addr; int /*<<< orphan*/  p_addr; int /*<<< orphan*/ * coef; TYPE_2__ ctl_f; int /*<<< orphan*/  ctl; int /*<<< orphan*/  size; scalar_t__ next; } ;
struct ioat2_dma_chan {int /*<<< orphan*/  base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  desc_id (struct ioat_ring_ent*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 scalar_t__ pq_get_src (void**,int) ; 
 int src_cnt_to_sw (int /*<<< orphan*/ ) ; 
 struct device* to_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_pq_desc_dbg(struct ioat2_dma_chan *ioat, struct ioat_ring_ent *desc, struct ioat_ring_ent *ext)
{
	struct device *dev = to_dev(&ioat->base);
	struct ioat_pq_descriptor *pq = desc->pq;
	struct ioat_pq_ext_descriptor *pq_ex = ext ? ext->pq_ex : NULL;
	struct ioat_raw_descriptor *descs[] = { (void *) pq, (void *) pq_ex };
	int src_cnt = src_cnt_to_sw(pq->ctl_f.src_cnt);
	int i;

	dev_dbg(dev, "desc[%d]: (%#llx->%#llx) flags: %#x"
		" sz: %#x ctl: %#x (op: %d int: %d compl: %d pq: '%s%s' src_cnt: %d)\n",
		desc_id(desc), (unsigned long long) desc->txd.phys,
		(unsigned long long) (pq_ex ? pq_ex->next : pq->next),
		desc->txd.flags, pq->size, pq->ctl, pq->ctl_f.op, pq->ctl_f.int_en,
		pq->ctl_f.compl_write,
		pq->ctl_f.p_disable ? "" : "p", pq->ctl_f.q_disable ? "" : "q",
		pq->ctl_f.src_cnt);
	for (i = 0; i < src_cnt; i++)
		dev_dbg(dev, "\tsrc[%d]: %#llx coef: %#x\n", i,
			(unsigned long long) pq_get_src(descs, i), pq->coef[i]);
	dev_dbg(dev, "\tP: %#llx\n", pq->p_addr);
	dev_dbg(dev, "\tQ: %#llx\n", pq->q_addr);
}