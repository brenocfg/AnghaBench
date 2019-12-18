#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mcp {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  mccr1; int /*<<< orphan*/  mccr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCCR0_MCE ; 
 int /*<<< orphan*/  Ser4MCCR0 ; 
 int /*<<< orphan*/  Ser4MCCR1 ; 
 struct mcp* platform_get_drvdata (struct platform_device*) ; 
 TYPE_1__* priv (struct mcp*) ; 

__attribute__((used)) static int mcp_sa11x0_suspend(struct platform_device *dev, pm_message_t state)
{
	struct mcp *mcp = platform_get_drvdata(dev);

	priv(mcp)->mccr0 = Ser4MCCR0;
	priv(mcp)->mccr1 = Ser4MCCR1;
	Ser4MCCR0 &= ~MCCR0_MCE;

	return 0;
}