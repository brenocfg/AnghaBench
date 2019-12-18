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
typedef  int u8 ;
struct srp_event_struct {scalar_t__ cmnd; } ;
struct srp_cmd {int buf_fmt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SRP_NO_DATA_DESC ; 
 int /*<<< orphan*/  scsi_dma_unmap (scalar_t__) ; 

__attribute__((used)) static void unmap_cmd_data(struct srp_cmd *cmd,
			   struct srp_event_struct *evt_struct,
			   struct device *dev)
{
	u8 out_fmt, in_fmt;

	out_fmt = cmd->buf_fmt >> 4;
	in_fmt = cmd->buf_fmt & ((1U << 4) - 1);

	if (out_fmt == SRP_NO_DATA_DESC && in_fmt == SRP_NO_DATA_DESC)
		return;

	if (evt_struct->cmnd)
		scsi_dma_unmap(evt_struct->cmnd);
}