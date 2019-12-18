#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct hwi_async_pdu_context {TYPE_1__* async_entry; } ;
struct TYPE_2__ {struct list_head data_busy_list; struct list_head header_busy_list; } ;

/* Variables and functions */

__attribute__((used)) static struct list_head *hwi_get_async_busy_list(struct hwi_async_pdu_context
					  *pasync_ctx, unsigned int is_header,
					  unsigned int host_write_ptr)
{
	if (is_header)
		return &pasync_ctx->async_entry[host_write_ptr].
		    header_busy_list;
	else
		return &pasync_ctx->async_entry[host_write_ptr].data_busy_list;
}