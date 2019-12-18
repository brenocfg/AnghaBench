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
struct work_request_hdr {int /*<<< orphan*/  wr_lo; int /*<<< orphan*/  wr_hi; } ;
struct tx_desc {int /*<<< orphan*/ * flit; } ;
struct sk_buff {int /*<<< orphan*/  destructor; scalar_t__ transport_header; scalar_t__ tail; scalar_t__ data; int /*<<< orphan*/  len; } ;
struct sge_txq {TYPE_1__* sdesc; struct tx_desc* desc; } ;
struct sg_ent {int dummy; } ;
struct adapter {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  deferred_unmap_destructor ; 
 scalar_t__ immediate (struct sk_buff*) ; 
 unsigned int make_sgl (struct sk_buff*,struct sg_ent*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct work_request_hdr*,int) ; 
 scalar_t__ need_skb_unmap () ; 
 int /*<<< orphan*/  setup_deferred_unmapping (struct sk_buff*,int /*<<< orphan*/ ,struct sg_ent*,unsigned int) ; 
 int /*<<< orphan*/  skb_transport_header (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  write_imm (struct tx_desc*,struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  write_wr_hdr_sgl (unsigned int,struct sk_buff*,struct tx_desc*,unsigned int,struct sge_txq*,struct sg_ent*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_ofld_wr(struct adapter *adap, struct sk_buff *skb,
			  struct sge_txq *q, unsigned int pidx,
			  unsigned int gen, unsigned int ndesc)
{
	unsigned int sgl_flits, flits;
	struct work_request_hdr *from;
	struct sg_ent *sgp, sgl[MAX_SKB_FRAGS / 2 + 1];
	struct tx_desc *d = &q->desc[pidx];

	if (immediate(skb)) {
		q->sdesc[pidx].skb = NULL;
		write_imm(d, skb, skb->len, gen);
		return;
	}

	/* Only TX_DATA builds SGLs */

	from = (struct work_request_hdr *)skb->data;
	memcpy(&d->flit[1], &from[1],
	       skb_transport_offset(skb) - sizeof(*from));

	flits = skb_transport_offset(skb) / 8;
	sgp = ndesc == 1 ? (struct sg_ent *)&d->flit[flits] : sgl;
	sgl_flits = make_sgl(skb, sgp, skb_transport_header(skb),
			     skb->tail - skb->transport_header,
			     adap->pdev);
	if (need_skb_unmap()) {
		setup_deferred_unmapping(skb, adap->pdev, sgp, sgl_flits);
		skb->destructor = deferred_unmap_destructor;
	}

	write_wr_hdr_sgl(ndesc, skb, d, pidx, q, sgl, flits, sgl_flits,
			 gen, from->wr_hi, from->wr_lo);
}