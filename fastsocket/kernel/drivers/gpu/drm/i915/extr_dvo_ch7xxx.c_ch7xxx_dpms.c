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
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH7xxx_PM ; 
 int CH7xxx_PM_DVIL ; 
 int CH7xxx_PM_DVIP ; 
 int CH7xxx_PM_FPD ; 
 int /*<<< orphan*/  ch7xxx_writeb (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ch7xxx_dpms(struct intel_dvo_device *dvo, bool enable)
{
	if (enable)
		ch7xxx_writeb(dvo, CH7xxx_PM, CH7xxx_PM_DVIL | CH7xxx_PM_DVIP);
	else
		ch7xxx_writeb(dvo, CH7xxx_PM, CH7xxx_PM_FPD);
}