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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct l4_kcq {size_t pg_host_opaque; scalar_t__ op_code; scalar_t__ status; int /*<<< orphan*/  pg_cid; } ;
struct cnic_sock {int /*<<< orphan*/  flags; int /*<<< orphan*/  pg_cid; } ;
struct cnic_local {struct cnic_sock* csk_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 scalar_t__ L4_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAIL ; 
 int /*<<< orphan*/  L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_UPDATE_PG ; 
 int /*<<< orphan*/  SK_F_OFFLD_SCHED ; 
 int /*<<< orphan*/  SK_F_PG_OFFLD_COMPLETE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_cm_conn_req (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_cm_upcall (struct cnic_local*,struct cnic_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_in_use (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_hold (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_put (struct cnic_sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_cm_process_offld_pg(struct cnic_dev *dev, struct l4_kcq *kcqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	u32 l5_cid = kcqe->pg_host_opaque;
	u8 opcode = kcqe->op_code;
	struct cnic_sock *csk = &cp->csk_tbl[l5_cid];

	csk_hold(csk);
	if (!cnic_in_use(csk))
		goto done;

	if (opcode == L4_KCQE_OPCODE_VALUE_UPDATE_PG) {
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		goto done;
	}
	/* Possible PG kcqe status:  SUCCESS, OFFLOADED_PG, or CTX_ALLOC_FAIL */
	if (kcqe->status == L4_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAIL) {
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		cnic_cm_upcall(cp, csk,
			       L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE);
		goto done;
	}

	csk->pg_cid = kcqe->pg_cid;
	set_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags);
	cnic_cm_conn_req(csk);

done:
	csk_put(csk);
}