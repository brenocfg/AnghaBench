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
struct rx_ring {size_t lbq_curr_idx; size_t lbq_len; int /*<<< orphan*/  lbq_free_cnt; struct bq_desc* lbq; } ;
struct bq_desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct bq_desc *ql_get_curr_lbuf(struct rx_ring *rx_ring)
{
	struct bq_desc *lbq_desc = &rx_ring->lbq[rx_ring->lbq_curr_idx];
	rx_ring->lbq_curr_idx++;
	if (rx_ring->lbq_curr_idx == rx_ring->lbq_len)
		rx_ring->lbq_curr_idx = 0;
	rx_ring->lbq_free_cnt++;
	return lbq_desc;
}