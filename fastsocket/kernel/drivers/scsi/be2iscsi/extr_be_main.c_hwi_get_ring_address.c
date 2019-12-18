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
struct phys_addr {int dummy; } ;
struct TYPE_4__ {struct phys_addr* ring_base; } ;
struct TYPE_3__ {struct phys_addr* ring_base; } ;
struct hwi_async_pdu_context {TYPE_2__ async_data; TYPE_1__ async_header; } ;

/* Variables and functions */

__attribute__((used)) static struct phys_addr *
hwi_get_ring_address(struct hwi_async_pdu_context *pasync_ctx,
		     unsigned int is_header, unsigned int host_write_ptr)
{
	struct phys_addr *pasync_sge = NULL;

	if (is_header)
		pasync_sge = pasync_ctx->async_header.ring_base;
	else
		pasync_sge = pasync_ctx->async_data.ring_base;

	return pasync_sge + host_write_ptr;
}