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
struct link_params {struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_set_e1e2_module_fault_led (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_e3_module_fault_led (struct link_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_set_sfp_module_fault_led(struct link_params *params,
					   u8 gpio_mode)
{
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ module fault LED to %d\n", gpio_mode);
	if (CHIP_IS_E3(bp)) {
		/* Low ==> if SFP+ module is supported otherwise
		 * High ==> if SFP+ module is not on the approved vendor list
		 */
		bnx2x_set_e3_module_fault_led(params, gpio_mode);
	} else
		bnx2x_set_e1e2_module_fault_led(params, gpio_mode);
}