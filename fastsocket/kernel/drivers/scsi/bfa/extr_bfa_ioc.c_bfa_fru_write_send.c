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
typedef  scalar_t__ u32 ;
struct bfi_fru_write_req_s {int last; int /*<<< orphan*/  alen; int /*<<< orphan*/  mh; int /*<<< orphan*/  trfr_cmpl; void* length; void* offset; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_fru_s {scalar_t__ addr_off; scalar_t__ offset; scalar_t__ residue; scalar_t__ ubuf; TYPE_1__ mb; int /*<<< orphan*/  ioc; int /*<<< orphan*/  dbuf_kva; int /*<<< orphan*/  dbuf_pa; int /*<<< orphan*/  trfr_cmpl; } ;
typedef  enum bfi_fru_h2i_msgs { ____Placeholder_bfi_fru_h2i_msgs } bfi_fru_h2i_msgs ;

/* Variables and functions */
 scalar_t__ BFA_FRU_DMA_BUF_SZ ; 
 int /*<<< orphan*/  BFI_MC_FRU ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
bfa_fru_write_send(void *cbarg, enum bfi_fru_h2i_msgs msg_type)
{
	struct bfa_fru_s *fru = cbarg;
	struct bfi_fru_write_req_s *msg =
			(struct bfi_fru_write_req_s *) fru->mb.msg;
	u32 len;

	msg->offset = cpu_to_be32(fru->addr_off + fru->offset);
	len = (fru->residue < BFA_FRU_DMA_BUF_SZ) ?
				fru->residue : BFA_FRU_DMA_BUF_SZ;
	msg->length = cpu_to_be32(len);

	/*
	 * indicate if it's the last msg of the whole write operation
	 */
	msg->last = (len == fru->residue) ? 1 : 0;

	msg->trfr_cmpl = (len == fru->residue) ? fru->trfr_cmpl : 0;
	bfi_h2i_set(msg->mh, BFI_MC_FRU, msg_type, bfa_ioc_portid(fru->ioc));
	bfa_alen_set(&msg->alen, len, fru->dbuf_pa);

	memcpy(fru->dbuf_kva, fru->ubuf + fru->offset, len);
	bfa_ioc_mbox_queue(fru->ioc, &fru->mb);

	fru->residue -= len;
	fru->offset += len;
}