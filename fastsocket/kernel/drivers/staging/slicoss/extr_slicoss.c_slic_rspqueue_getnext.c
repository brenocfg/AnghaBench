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
typedef  int u32 ;
struct slic_rspqueue {int offset; int* paddr; size_t pageindex; int num_pages; struct slic_rspbuf* rspbuf; scalar_t__* vaddr; } ;
struct slic_rspbuf {int status; int hosthandle; } ;
struct adapter {TYPE_1__* slic_regs; struct slic_rspqueue rspqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  slic_addr_upper; int /*<<< orphan*/  slic_rbar64; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DONT_FLUSH ; 
 int SLIC_RSPQ_BUFSINPAGE ; 
 int /*<<< orphan*/  slic_reg64_write (struct adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct slic_rspbuf *slic_rspqueue_getnext(struct adapter *adapter)
{
	struct slic_rspqueue *rspq = &adapter->rspqueue;
	struct slic_rspbuf *buf;

	if (!(rspq->rspbuf->status))
		return NULL;

	buf = rspq->rspbuf;
#ifndef CONFIG_X86_64
	ASSERT((buf->status & 0xFFFFFFE0) == 0);
#endif
	ASSERT(buf->hosthandle);
	if (++rspq->offset < SLIC_RSPQ_BUFSINPAGE) {
		rspq->rspbuf++;
#ifndef CONFIG_X86_64
		ASSERT(((u32) rspq->rspbuf & 0xFFFFFFE0) ==
		       (u32) rspq->rspbuf);
#endif
	} else {
		ASSERT(rspq->offset == SLIC_RSPQ_BUFSINPAGE);
		slic_reg64_write(adapter, &adapter->slic_regs->slic_rbar64,
			(rspq->paddr[rspq->pageindex] | SLIC_RSPQ_BUFSINPAGE),
			&adapter->slic_regs->slic_addr_upper, 0, DONT_FLUSH);
		rspq->pageindex = (++rspq->pageindex) % rspq->num_pages;
		rspq->offset = 0;
		rspq->rspbuf = (struct slic_rspbuf *)
						rspq->vaddr[rspq->pageindex];
#ifndef CONFIG_X86_64
		ASSERT(((u32) rspq->rspbuf & 0xFFFFF000) ==
		       (u32) rspq->rspbuf);
#endif
	}
#ifndef CONFIG_X86_64
	ASSERT(((u32) buf & 0xFFFFFFE0) == (u32) buf);
#endif
	return buf;
}