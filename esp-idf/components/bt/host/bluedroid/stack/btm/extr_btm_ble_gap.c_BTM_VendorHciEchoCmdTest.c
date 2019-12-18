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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_VendorHciEchoCmdCallback ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_VENDOR_COMMON_ECHO_CMD_OPCODE ; 

void BTM_VendorHciEchoCmdTest(uint8_t echo)
{
    BTM_VendorSpecificCommand (HCI_VENDOR_COMMON_ECHO_CMD_OPCODE,
                                1,
                                &echo,
                                BTM_VendorHciEchoCmdCallback);
}