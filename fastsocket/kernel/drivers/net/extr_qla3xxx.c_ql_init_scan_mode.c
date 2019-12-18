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
struct ql3_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_LINK_OPTICAL ; 
 int /*<<< orphan*/  ql_mii_enable_scan_mode (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_petbi_init_ex (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_phy_init_ex (struct ql3_adapter*) ; 
 scalar_t__ ql_this_adapter_controls_port (struct ql3_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_init_scan_mode(struct ql3_adapter *qdev)
{
	ql_mii_enable_scan_mode(qdev);

	if (test_bit(QL_LINK_OPTICAL,&qdev->flags)) {
		if (ql_this_adapter_controls_port(qdev))
			ql_petbi_init_ex(qdev);
	} else {
		if (ql_this_adapter_controls_port(qdev))
			ql_phy_init_ex(qdev);
	}
}