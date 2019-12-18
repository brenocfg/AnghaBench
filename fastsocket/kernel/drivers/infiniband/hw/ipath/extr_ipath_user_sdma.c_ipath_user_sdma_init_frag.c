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
struct page {int dummy; } ;
struct ipath_user_sdma_pkt {TYPE_1__* addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {size_t offset; size_t length; int put_page; int dma_mapped; int /*<<< orphan*/  addr; void* kvaddr; struct page* page; } ;

/* Variables and functions */

__attribute__((used)) static void ipath_user_sdma_init_frag(struct ipath_user_sdma_pkt *pkt,
				      int i, size_t offset, size_t len,
				      int put_page, int dma_mapped,
				      struct page *page,
				      void *kvaddr, dma_addr_t dma_addr)
{
	pkt->addr[i].offset = offset;
	pkt->addr[i].length = len;
	pkt->addr[i].put_page = put_page;
	pkt->addr[i].dma_mapped = dma_mapped;
	pkt->addr[i].page = page;
	pkt->addr[i].kvaddr = kvaddr;
	pkt->addr[i].addr = dma_addr;
}