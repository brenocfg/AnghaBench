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
struct scsi_cmnd {int dummy; } ;
struct pvscsi_ctx {struct scsi_cmnd* cmd; } ;
struct pvscsi_adapter {size_t req_depth; struct pvscsi_ctx* cmd_map; } ;

/* Variables and functions */

__attribute__((used)) static struct pvscsi_ctx *
pvscsi_find_context(const struct pvscsi_adapter *adapter, struct scsi_cmnd *cmd)
{
	struct pvscsi_ctx *ctx, *end;

	end = &adapter->cmd_map[adapter->req_depth];
	for (ctx = adapter->cmd_map; ctx < end; ctx++)
		if (ctx->cmd == cmd)
			return ctx;

	return NULL;
}