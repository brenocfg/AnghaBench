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
struct isp1301 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_MODE_CONTROL_1 ; 
 int /*<<< orphan*/  MC1_DAT_SE0 ; 
 int /*<<< orphan*/  MC1_SUSPEND ; 
 int /*<<< orphan*/  isp1301_clear_bits (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1301_set_bits (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void power_up(struct isp1301 *isp)
{
	// isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_2, MC2_GLOBAL_PWR_DN);
	isp1301_clear_bits(isp, ISP1301_MODE_CONTROL_1, MC1_SUSPEND);

	/* do this only when cpu is driving transceiver,
	 * so host won't see a low speed device...
	 */
	isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1, MC1_DAT_SE0);
}