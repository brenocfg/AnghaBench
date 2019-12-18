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
struct scsi_host_cmd_pool {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct scsi_host_cmd_pool* scsi_get_host_cmd_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_pool_free_command (struct scsi_host_cmd_pool*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_put_host_cmd_pool (int /*<<< orphan*/ ) ; 

void scsi_free_command(gfp_t gfp_mask, struct scsi_cmnd *cmd)
{
	struct scsi_host_cmd_pool *pool = scsi_get_host_cmd_pool(gfp_mask);

	/*
	 * this could trigger if the mask to scsi_allocate_command
	 * doesn't match this mask.  Otherwise we're guaranteed that this
	 * succeeds because scsi_allocate_command must have taken a reference
	 * on the pool
	 */
	BUG_ON(!pool);

	scsi_pool_free_command(pool, cmd);
	/*
	 * scsi_put_host_cmd_pool is called twice; once to release the
	 * reference we took above, and once to release the reference
	 * originally taken by scsi_allocate_command
	 */
	scsi_put_host_cmd_pool(gfp_mask);
	scsi_put_host_cmd_pool(gfp_mask);
}