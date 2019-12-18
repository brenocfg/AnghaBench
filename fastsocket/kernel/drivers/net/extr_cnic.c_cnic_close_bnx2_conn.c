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
typedef  int /*<<< orphan*/  u32 ;
struct cnic_sock {int /*<<< orphan*/  state; int /*<<< orphan*/  flags; struct cnic_dev* dev; } ;
struct cnic_local {int dummy; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  L4_KCQE_OPCODE_VALUE_RESET_RECEIVED ; 
 int /*<<< orphan*/  SK_F_CONNECT_START ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_close_conn (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_cm_upcall (struct cnic_local*,struct cnic_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_close_bnx2_conn(struct cnic_sock *csk, u32 opcode)
{
	struct cnic_dev *dev = csk->dev;
	struct cnic_local *cp = dev->cnic_priv;

	if (opcode == L4_KCQE_OPCODE_VALUE_RESET_RECEIVED) {
		cnic_cm_upcall(cp, csk, opcode);
		return;
	}

	clear_bit(SK_F_CONNECT_START, &csk->flags);
	cnic_close_conn(csk);
	csk->state = opcode;
	cnic_cm_upcall(cp, csk, opcode);
}