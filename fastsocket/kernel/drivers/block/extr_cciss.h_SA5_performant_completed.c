#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* reply_pool_head; int reply_pool_wraparound; unsigned long* reply_pool; int max_commands; int /*<<< orphan*/  commands_outstanding; scalar_t__ vaddr; scalar_t__ msix_vector; scalar_t__ msi_vector; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 unsigned long FIFO_EMPTY ; 
 scalar_t__ SA5_OUTDB_CLEAR ; 
 int /*<<< orphan*/  SA5_OUTDB_CLEAR_PERF_BIT ; 
 scalar_t__ SA5_OUTDB_STATUS ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long SA5_performant_completed(ctlr_info_t *h)
{
	unsigned long register_value = FIFO_EMPTY;

	/* flush the controller write of the reply queue by reading
	 * outbound doorbell status register.
	 */
	register_value = readl(h->vaddr + SA5_OUTDB_STATUS);
	/* msi auto clears the interrupt pending bit. */
	if (!(h->msi_vector || h->msix_vector)) {
		writel(SA5_OUTDB_CLEAR_PERF_BIT, h->vaddr + SA5_OUTDB_CLEAR);
		/* Do a read in order to flush the write to the controller
		 * (as per spec.)
		 */
		register_value = readl(h->vaddr + SA5_OUTDB_STATUS);
	}

	if ((*(h->reply_pool_head) & 1) == (h->reply_pool_wraparound)) {
		register_value = *(h->reply_pool_head);
		(h->reply_pool_head)++;
		h->commands_outstanding--;
	} else {
		register_value = FIFO_EMPTY;
	}
	/* Check for wraparound */
	if (h->reply_pool_head == (h->reply_pool + h->max_commands)) {
		h->reply_pool_head = h->reply_pool;
		h->reply_pool_wraparound ^= 1;
	}

	return register_value;
}