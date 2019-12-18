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
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFP410_CTL_1 ; 
 int /*<<< orphan*/  TFP410_CTL_1_PD ; 
 int /*<<< orphan*/  tfp410_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfp410_writeb (struct intel_dvo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tfp410_dpms(struct intel_dvo_device *dvo, bool enable)
{
	uint8_t ctl1;

	if (!tfp410_readb(dvo, TFP410_CTL_1, &ctl1))
		return;

	if (enable)
		ctl1 |= TFP410_CTL_1_PD;
	else
		ctl1 &= ~TFP410_CTL_1_PD;

	tfp410_writeb(dvo, TFP410_CTL_1, ctl1);
}