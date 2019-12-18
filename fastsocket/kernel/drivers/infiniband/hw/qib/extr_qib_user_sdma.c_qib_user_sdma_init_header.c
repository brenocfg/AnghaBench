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
struct qib_user_sdma_pkt {int naddr; int /*<<< orphan*/  counter; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  qib_user_sdma_init_frag (struct qib_user_sdma_pkt*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int,struct page*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_user_sdma_init_header(struct qib_user_sdma_pkt *pkt,
				      u32 counter, size_t offset,
				      size_t len, int dma_mapped,
				      struct page *page,
				      void *kvaddr, dma_addr_t dma_addr)
{
	pkt->naddr = 1;
	pkt->counter = counter;
	qib_user_sdma_init_frag(pkt, 0, offset, len, 0, dma_mapped, page,
				kvaddr, dma_addr);
}