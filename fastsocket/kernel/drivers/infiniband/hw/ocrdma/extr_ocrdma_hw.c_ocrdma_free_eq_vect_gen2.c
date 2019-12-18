#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int start_vector; } ;
struct TYPE_4__ {TYPE_1__ msix; } ;
struct ocrdma_dev {TYPE_2__ nic_info; } ;

/* Variables and functions */

__attribute__((used)) static void ocrdma_free_eq_vect_gen2(struct ocrdma_dev *dev)
{
	/* this assumes that EQs are freed in exactly reverse order
	 * as its allocation.
	 */
	dev->nic_info.msix.start_vector -= 1;
}