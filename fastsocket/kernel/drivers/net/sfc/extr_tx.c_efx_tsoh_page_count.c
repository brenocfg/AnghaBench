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
struct efx_tx_queue {scalar_t__ ptr_mask; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (scalar_t__,int) ; 
 int TSOH_PER_PAGE ; 

__attribute__((used)) static unsigned int efx_tsoh_page_count(struct efx_tx_queue *tx_queue)
{
	return DIV_ROUND_UP(tx_queue->ptr_mask + 1, 2 * TSOH_PER_PAGE);
}