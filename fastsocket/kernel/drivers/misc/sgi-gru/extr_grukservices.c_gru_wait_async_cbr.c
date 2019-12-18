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
struct gru_blade_state {int /*<<< orphan*/  bs_async_wq; } ;

/* Variables and functions */
 struct gru_blade_state* ASYNC_HAN_TO_BS (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 

void gru_wait_async_cbr(unsigned long han)
{
	struct gru_blade_state *bs = ASYNC_HAN_TO_BS(han);

	wait_for_completion(bs->bs_async_wq);
	mb();
}