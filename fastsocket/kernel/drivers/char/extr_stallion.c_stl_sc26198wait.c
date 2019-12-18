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
struct stlport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSTR ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*) ; 
 int /*<<< orphan*/  stl_sc26198getglobreg (struct stlport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stl_sc26198wait(struct stlport *portp)
{
	int	i;

	pr_debug("stl_sc26198wait(portp=%p)\n", portp);

	if (portp == NULL)
		return;

	for (i = 0; i < 20; i++)
		stl_sc26198getglobreg(portp, TSTR);
}