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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u64 ;
struct TYPE_8__ {void* pa; int /*<<< orphan*/ * kva; } ;
struct TYPE_7__ {TYPE_4__ addr; } ;
struct TYPE_5__ {void* pa; int /*<<< orphan*/ * kva; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct bfa_msgq {TYPE_3__ rspq; TYPE_2__ cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 int /*<<< orphan*/  BFA_MSGQ_CMDQ_SIZE ; 
 scalar_t__ roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_msgq_memclaim(struct bfa_msgq *msgq, u8 *kva, u64 pa)
{
	msgq->cmdq.addr.kva = kva;
	msgq->cmdq.addr.pa  = pa;

	kva += roundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_ALIGN_SZ);
	pa += roundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_ALIGN_SZ);

	msgq->rspq.addr.kva = kva;
	msgq->rspq.addr.pa = pa;
}