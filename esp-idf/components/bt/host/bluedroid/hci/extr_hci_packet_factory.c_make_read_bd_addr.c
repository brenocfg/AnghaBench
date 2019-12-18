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
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_READ_BD_ADDR ; 
 int /*<<< orphan*/ * make_command_no_params (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BT_HDR *make_read_bd_addr(void)
{
    return make_command_no_params(HCI_READ_BD_ADDR);
}