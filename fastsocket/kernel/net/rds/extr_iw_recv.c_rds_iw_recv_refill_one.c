#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rds_iw_recv_work {TYPE_3__* r_frag; int /*<<< orphan*/  r_sge; TYPE_1__* r_iwinc; } ;
struct TYPE_8__ {scalar_t__ f_offset; int /*<<< orphan*/ * f_page; } ;
struct rds_iw_connection {TYPE_4__ i_frag; struct rds_iw_recv_work* i_recvs; void* i_recv_hdrs_dma; TYPE_2__* i_cm_id; } ;
struct rds_header {int dummy; } ;
struct rds_connection {int /*<<< orphan*/  c_faddr; struct rds_iw_connection* c_transport_data; } ;
struct ib_sge {int length; void* addr; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* dma_addr_t ;
struct TYPE_7__ {scalar_t__ f_offset; int /*<<< orphan*/ * f_page; void* f_mapped; int /*<<< orphan*/  f_item; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  ii_inc; int /*<<< orphan*/  ii_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RDS_FRAG_SIZE ; 
 scalar_t__ RDS_PAGE_LAST_OFF ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ *) ; 
 void* ib_dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_inc_init (int /*<<< orphan*/ *,struct rds_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_allocation ; 
 struct ib_sge* rds_iw_data_sge (struct rds_iw_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_frag_slab ; 
 struct ib_sge* rds_iw_header_sge (struct rds_iw_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_incoming_slab ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_sysctl_max_recv_allocation ; 
 int /*<<< orphan*/  s_iw_rx_alloc_limit ; 

__attribute__((used)) static int rds_iw_recv_refill_one(struct rds_connection *conn,
				  struct rds_iw_recv_work *recv,
				  gfp_t kptr_gfp, gfp_t page_gfp)
{
	struct rds_iw_connection *ic = conn->c_transport_data;
	dma_addr_t dma_addr;
	struct ib_sge *sge;
	int ret = -ENOMEM;

	if (!recv->r_iwinc) {
		if (!atomic_add_unless(&rds_iw_allocation, 1, rds_iw_sysctl_max_recv_allocation)) {
			rds_iw_stats_inc(s_iw_rx_alloc_limit);
			goto out;
		}
		recv->r_iwinc = kmem_cache_alloc(rds_iw_incoming_slab,
						 kptr_gfp);
		if (!recv->r_iwinc) {
			atomic_dec(&rds_iw_allocation);
			goto out;
		}
		INIT_LIST_HEAD(&recv->r_iwinc->ii_frags);
		rds_inc_init(&recv->r_iwinc->ii_inc, conn, conn->c_faddr);
	}

	if (!recv->r_frag) {
		recv->r_frag = kmem_cache_alloc(rds_iw_frag_slab, kptr_gfp);
		if (!recv->r_frag)
			goto out;
		INIT_LIST_HEAD(&recv->r_frag->f_item);
		recv->r_frag->f_page = NULL;
	}

	if (!ic->i_frag.f_page) {
		ic->i_frag.f_page = alloc_page(page_gfp);
		if (!ic->i_frag.f_page)
			goto out;
		ic->i_frag.f_offset = 0;
	}

	dma_addr = ib_dma_map_page(ic->i_cm_id->device,
				  ic->i_frag.f_page,
				  ic->i_frag.f_offset,
				  RDS_FRAG_SIZE,
				  DMA_FROM_DEVICE);
	if (ib_dma_mapping_error(ic->i_cm_id->device, dma_addr))
		goto out;

	/*
	 * Once we get the RDS_PAGE_LAST_OFF frag then rds_iw_frag_unmap()
	 * must be called on this recv.  This happens as completions hit
	 * in order or on connection shutdown.
	 */
	recv->r_frag->f_page = ic->i_frag.f_page;
	recv->r_frag->f_offset = ic->i_frag.f_offset;
	recv->r_frag->f_mapped = dma_addr;

	sge = rds_iw_data_sge(ic, recv->r_sge);
	sge->addr = dma_addr;
	sge->length = RDS_FRAG_SIZE;

	sge = rds_iw_header_sge(ic, recv->r_sge);
	sge->addr = ic->i_recv_hdrs_dma + (recv - ic->i_recvs) * sizeof(struct rds_header);
	sge->length = sizeof(struct rds_header);

	get_page(recv->r_frag->f_page);

	if (ic->i_frag.f_offset < RDS_PAGE_LAST_OFF) {
		ic->i_frag.f_offset += RDS_FRAG_SIZE;
	} else {
		put_page(ic->i_frag.f_page);
		ic->i_frag.f_page = NULL;
		ic->i_frag.f_offset = 0;
	}

	ret = 0;
out:
	return ret;
}