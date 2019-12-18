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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int FSP_BIT_EN_REG_CLK ; 
 int /*<<< orphan*/  FSP_REG_SYSCTL1 ; 
 int fsp_reg_read (struct psmouse*,int /*<<< orphan*/ ,int*) ; 
 int fsp_reg_write (struct psmouse*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsp_reg_write_enable(struct psmouse *psmouse, bool enable)
{
	int v, nv;

	if (fsp_reg_read(psmouse, FSP_REG_SYSCTL1, &v) == -1)
		return -1;

	if (enable)
		nv = v | FSP_BIT_EN_REG_CLK;
	else
		nv = v & ~FSP_BIT_EN_REG_CLK;

	/* only write if necessary */
	if (nv != v)
		if (fsp_reg_write(psmouse, FSP_REG_SYSCTL1, nv) == -1)
			return -1;

	return 0;
}