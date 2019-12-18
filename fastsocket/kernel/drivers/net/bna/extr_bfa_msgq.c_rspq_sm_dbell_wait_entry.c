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
struct bfa_msgq_rspq {TYPE_1__* msgq; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_msgq_rspq_dbell (struct bfa_msgq_rspq*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_is_disabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rspq_sm_dbell_wait_entry(struct bfa_msgq_rspq *rspq)
{
	if (!bfa_nw_ioc_is_disabled(rspq->msgq->ioc))
		bfa_msgq_rspq_dbell(rspq);
}