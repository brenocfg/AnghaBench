#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct usb_dt9812 {TYPE_1__ command_write; int /*<<< orphan*/  udev; } ;
struct TYPE_5__ {int count; struct dt9812_rmw_byte* rmw; } ;
struct TYPE_6__ {TYPE_2__ rmw_multi_info; } ;
struct dt9812_usb_cmd {TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct dt9812_rmw_byte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT9812_RMW_MULTI_BYTE_REG ; 
 int HZ ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dt9812_usb_cmd*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt9812_rmw_multiple_registers(struct usb_dt9812 *dev, int reg_count,
					 struct dt9812_rmw_byte *rmw)
{
	struct dt9812_usb_cmd cmd;
	int i, count, retval;

	cmd.cmd = cpu_to_le32(DT9812_RMW_MULTI_BYTE_REG);
	cmd.u.rmw_multi_info.count = reg_count;
	for (i = 0; i < reg_count; i++)
		cmd.u.rmw_multi_info.rmw[i] = rmw[i];

	/* DT9812 only responds to 32 byte writes!! */
	retval = usb_bulk_msg(dev->udev,
			      usb_sndbulkpipe(dev->udev,
					      dev->command_write.addr),
			      &cmd, 32, &count, HZ * 1);
	return retval;
}