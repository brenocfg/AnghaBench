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
struct backing_dev_info {int /*<<< orphan*/  state; } ;
typedef  enum bdi_state { ____Placeholder_bdi_state } bdi_state ;

/* Variables and functions */
 int BDI_async_congested ; 
 int BDI_sync_congested ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nr_bdi_congested ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

void set_bdi_congested(struct backing_dev_info *bdi, int sync)
{
	enum bdi_state bit;

	bit = sync ? BDI_sync_congested : BDI_async_congested;
	if (!test_and_set_bit(bit, &bdi->state))
		atomic_inc(&nr_bdi_congested[sync]);
}