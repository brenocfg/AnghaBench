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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnic_rq {int dummy; } ;
struct rq_enet_desc {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_ENET_TYPE_NOT_SOP ; 
 int /*<<< orphan*/  RQ_ENET_TYPE_ONLY_SOP ; 
 int VNIC_PADDR_TARGET ; 
 int /*<<< orphan*/  rq_enet_desc_enc (struct rq_enet_desc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rq_enet_desc* vnic_rq_next_desc (struct vnic_rq*) ; 
 int /*<<< orphan*/  vnic_rq_post (struct vnic_rq*,void*,unsigned int,scalar_t__,unsigned int) ; 

__attribute__((used)) static inline void enic_queue_rq_desc(struct vnic_rq *rq,
	void *os_buf, unsigned int os_buf_index,
	dma_addr_t dma_addr, unsigned int len)
{
	struct rq_enet_desc *desc = vnic_rq_next_desc(rq);
	u8 type = os_buf_index ?
		RQ_ENET_TYPE_NOT_SOP : RQ_ENET_TYPE_ONLY_SOP;

	rq_enet_desc_enc(desc,
		(u64)dma_addr | VNIC_PADDR_TARGET,
		type, (u16)len);

	vnic_rq_post(rq, os_buf, os_buf_index, dma_addr, len);
}