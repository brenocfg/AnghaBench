#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pwm_channel {int /*<<< orphan*/  index; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_CCNT ; 
 int /*<<< orphan*/  PWM_CDTY ; 
 int /*<<< orphan*/  PWM_CMR ; 
 int /*<<< orphan*/  PWM_CPRD ; 
 int /*<<< orphan*/  PWM_IMR ; 
 int /*<<< orphan*/  PWM_MR ; 
 int /*<<< orphan*/  PWM_SR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* pwm ; 
 int /*<<< orphan*/  pwm_channel_readl (struct pwm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_readl (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_dumpregs(struct pwm_channel *ch, char *tag)
{
	struct device	*dev = &pwm->pdev->dev;

	dev_dbg(dev, "%s: mr %08x, sr %08x, imr %08x\n",
		tag,
		pwm_readl(pwm, PWM_MR),
		pwm_readl(pwm, PWM_SR),
		pwm_readl(pwm, PWM_IMR));
	dev_dbg(dev,
		"pwm ch%d - mr %08x, dty %u, prd %u, cnt %u\n",
		ch->index,
		pwm_channel_readl(ch, PWM_CMR),
		pwm_channel_readl(ch, PWM_CDTY),
		pwm_channel_readl(ch, PWM_CPRD),
		pwm_channel_readl(ch, PWM_CCNT));
}