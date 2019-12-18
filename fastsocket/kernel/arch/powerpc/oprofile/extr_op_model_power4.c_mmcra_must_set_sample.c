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
 int /*<<< orphan*/  PV_970 ; 
 int /*<<< orphan*/  PV_970FX ; 
 int /*<<< orphan*/  PV_970GX ; 
 int /*<<< orphan*/  PV_970MP ; 
 int /*<<< orphan*/  PV_POWER4 ; 
 int /*<<< orphan*/  PV_POWER4p ; 
 scalar_t__ __is_processor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mmcra_must_set_sample(void)
{
	if (__is_processor(PV_POWER4) || __is_processor(PV_POWER4p) ||
	    __is_processor(PV_970) || __is_processor(PV_970FX) ||
	    __is_processor(PV_970MP) || __is_processor(PV_970GX))
		return 1;

	return 0;
}