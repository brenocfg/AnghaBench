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
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  attr; scalar_t__ ignore_gfp_wait; } ;

/* Variables and functions */
 int __GFP_NOFAIL ; 
 int __GFP_WAIT ; 
 TYPE_1__ failslab ; 
 int should_fail (int /*<<< orphan*/ *,size_t) ; 

bool should_failslab(size_t size, gfp_t gfpflags)
{
	if (gfpflags & __GFP_NOFAIL)
		return false;

        if (failslab.ignore_gfp_wait && (gfpflags & __GFP_WAIT))
		return false;

	return should_fail(&failslab.attr, size);
}