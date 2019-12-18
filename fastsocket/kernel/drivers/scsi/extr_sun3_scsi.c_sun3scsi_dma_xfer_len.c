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
struct scsi_cmnd {TYPE_1__* request; } ;
struct TYPE_2__ {scalar_t__ cmd_type; } ;

/* Variables and functions */
 scalar_t__ REQ_TYPE_FS ; 

__attribute__((used)) static inline unsigned long sun3scsi_dma_xfer_len(unsigned long wanted,
						  struct scsi_cmnd *cmd,
						  int write_flag)
{
	if (cmd->request->cmd_type == REQ_TYPE_FS)
 		return wanted;
	else
		return 0;
}