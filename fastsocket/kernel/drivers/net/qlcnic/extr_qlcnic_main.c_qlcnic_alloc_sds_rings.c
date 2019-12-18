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
struct qlcnic_recv_context {int /*<<< orphan*/ * sds_rings; } ;
struct qlcnic_host_sds_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

int qlcnic_alloc_sds_rings(struct qlcnic_recv_context *recv_ctx, int count)
{
	int size = sizeof(struct qlcnic_host_sds_ring) * count;

	recv_ctx->sds_rings = kzalloc(size, GFP_KERNEL);

	return recv_ctx->sds_rings == NULL;
}