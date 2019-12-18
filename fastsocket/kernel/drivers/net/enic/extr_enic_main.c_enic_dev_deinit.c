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
struct enic {unsigned int rq_count; int /*<<< orphan*/ * napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  enic_clear_intr_mode (struct enic*) ; 
 int /*<<< orphan*/  enic_free_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enic_dev_deinit(struct enic *enic)
{
	unsigned int i;

	for (i = 0; i < enic->rq_count; i++)
		netif_napi_del(&enic->napi[i]);

	enic_free_vnic_resources(enic);
	enic_clear_intr_mode(enic);
}