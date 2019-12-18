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
struct vreg {unsigned int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCOM_VREG_SWITCH ; 
 int /*<<< orphan*/  msm_proc_comm (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

void vreg_disable(struct vreg *vreg)
{
	unsigned id = vreg->id;
	unsigned enable = 0;
	msm_proc_comm(PCOM_VREG_SWITCH, &id, &enable);
}