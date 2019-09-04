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
typedef  int /*<<< orphan*/  prof_tctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  huge_prof_tctx_set (void const*,int /*<<< orphan*/ *) ; 

void
huge_prof_tctx_reset(const void *ptr)
{

	huge_prof_tctx_set(ptr, (prof_tctx_t *)(uintptr_t)1U);
}