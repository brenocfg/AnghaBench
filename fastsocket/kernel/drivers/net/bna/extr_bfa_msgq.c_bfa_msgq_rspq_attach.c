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
struct bfa_msgq_rspq {struct bfa_msgq* msgq; int /*<<< orphan*/  depth; } ;
struct bfa_msgq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_MSGQ_RSPQ_NUM_ENTRY ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_msgq_rspq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspq_sm_stopped ; 

__attribute__((used)) static void
bfa_msgq_rspq_attach(struct bfa_msgq_rspq *rspq, struct bfa_msgq *msgq)
{
	rspq->depth = BFA_MSGQ_RSPQ_NUM_ENTRY;
	rspq->msgq = msgq;
	bfa_fsm_set_state(rspq, rspq_sm_stopped);
}