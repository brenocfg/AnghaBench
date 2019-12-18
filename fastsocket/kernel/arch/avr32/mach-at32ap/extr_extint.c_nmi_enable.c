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

/* Variables and functions */
 int /*<<< orphan*/  EIC_NMIC_ENABLE ; 
 int /*<<< orphan*/  NMIC ; 
 int /*<<< orphan*/  eic_writel (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nmi_eic ; 
 int nmi_enabled ; 

int nmi_enable(void)
{
	nmi_enabled = true;

	if (nmi_eic)
		eic_writel(nmi_eic, NMIC, EIC_NMIC_ENABLE);

	return 0;
}