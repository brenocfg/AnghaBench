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
struct ocrdma_ah {int /*<<< orphan*/  dev; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 struct ocrdma_ah* get_ocrdma_ah (struct ib_ah*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_ah*) ; 
 int /*<<< orphan*/  ocrdma_free_av (int /*<<< orphan*/ ,struct ocrdma_ah*) ; 

int ocrdma_destroy_ah(struct ib_ah *ibah)
{
	struct ocrdma_ah *ah = get_ocrdma_ah(ibah);
	ocrdma_free_av(ah->dev, ah);
	kfree(ah);
	return 0;
}