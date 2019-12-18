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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct be_adapter {int /*<<< orphan*/  hba_port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_NO_LOOPBACK ; 
 int /*<<< orphan*/  be_cmd_loopback_test (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  be_cmd_set_loopback (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 be_loopback_test(struct be_adapter *adapter, u8 loopback_type,
				u64 *status)
{
	be_cmd_set_loopback(adapter, adapter->hba_port_num,
				loopback_type, 1);
	*status = be_cmd_loopback_test(adapter, adapter->hba_port_num,
				loopback_type, 1500,
				2, 0xabc);
	be_cmd_set_loopback(adapter, adapter->hba_port_num,
				BE_NO_LOOPBACK, 1);
	return *status;
}