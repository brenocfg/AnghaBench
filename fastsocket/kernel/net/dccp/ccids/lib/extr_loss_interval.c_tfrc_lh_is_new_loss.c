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
typedef  int u8 ;
struct tfrc_rx_hist_entry {int /*<<< orphan*/  tfrchrx_ccval; int /*<<< orphan*/  tfrchrx_seqno; } ;
struct tfrc_loss_interval {int /*<<< orphan*/  li_ccval; scalar_t__ li_is_closed; int /*<<< orphan*/  li_seqno; } ;

/* Variables and functions */
 int SUB16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_delta_seqno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 tfrc_lh_is_new_loss(struct tfrc_loss_interval *cur,
				     struct tfrc_rx_hist_entry *new_loss)
{
	return	dccp_delta_seqno(cur->li_seqno, new_loss->tfrchrx_seqno) > 0 &&
		(cur->li_is_closed || SUB16(new_loss->tfrchrx_ccval, cur->li_ccval) > 4);
}