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
struct isci_request {scalar_t__ request_daddr; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline dma_addr_t
sci_io_request_get_dma_addr(struct isci_request *ireq, void *virt_addr)
{

	char *requested_addr = (char *)virt_addr;
	char *base_addr = (char *)ireq;

	BUG_ON(requested_addr < base_addr);
	BUG_ON((requested_addr - base_addr) >= sizeof(*ireq));

	return ireq->request_daddr + (requested_addr - base_addr);
}