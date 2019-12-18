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
typedef  int /*<<< orphan*/  u32 ;
struct pvscsi_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_INTR_STATUS ; 
 int /*<<< orphan*/  pvscsi_reg_read (struct pvscsi_adapter const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pvscsi_read_intr_status(const struct pvscsi_adapter *adapter)
{
	return pvscsi_reg_read(adapter, PVSCSI_REG_OFFSET_INTR_STATUS);
}