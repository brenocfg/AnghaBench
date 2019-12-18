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
 struct scsi_host_cmd_pool* scsi_get_host_cmd_pool (int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* scsi_pool_alloc_command (struct scsi_host_cmd_pool*,int /*<<< orphan*/ ) ; 

struct scsi_cmnd *scsi_allocate_command(gfp_t gfp_mask)
{
	struct scsi_host_cmd_pool *pool = scsi_get_host_cmd_pool(gfp_mask);

	if (!pool)
		return NULL;

	return scsi_pool_alloc_command(pool, gfp_mask);
}