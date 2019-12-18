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
 int /*<<< orphan*/  PCOM_VREG_SET_LEVEL ; 
 int msm_proc_comm (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

int vreg_set_level(struct vreg *vreg, unsigned mv)
{
	unsigned id = vreg->id;
	return msm_proc_comm(PCOM_VREG_SET_LEVEL, &id, &mv);
}