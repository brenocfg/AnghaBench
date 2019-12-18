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
struct virtio_scsi_cmd {scalar_t__ comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (scalar_t__) ; 
 int /*<<< orphan*/  mempool_free (struct virtio_scsi_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtscsi_cmd_pool ; 

__attribute__((used)) static void virtscsi_complete_free(void *buf)
{
	struct virtio_scsi_cmd *cmd = buf;

	if (cmd->comp)
		complete_all(cmd->comp);
	else
		mempool_free(cmd, virtscsi_cmd_pool);
}