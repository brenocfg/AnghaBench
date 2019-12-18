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
struct pvscsi_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_KICK_RW_IO ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_adapter const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvscsi_kick_rw_io(const struct pvscsi_adapter *adapter)
{
	pvscsi_reg_write(adapter, PVSCSI_REG_OFFSET_KICK_RW_IO, 0);
}