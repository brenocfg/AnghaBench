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
 int EIO ; 
 int /*<<< orphan*/  FSP_REG_REVISION ; 
 scalar_t__ fsp_reg_read (struct psmouse*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fsp_get_revision(struct psmouse *psmouse, int *rev)
{
	if (fsp_reg_read(psmouse, FSP_REG_REVISION, rev))
		return -EIO;

	return 0;
}