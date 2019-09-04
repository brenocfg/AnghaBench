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
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert_zu_eq (size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_lg_prof_sample () ; 
 int /*<<< orphan*/  mallctl (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int) ; 

__attribute__((used)) static void
do_prof_reset(size_t lg_prof_sample)
{
	assert_d_eq(mallctl("prof.reset", NULL, NULL,
	    &lg_prof_sample, sizeof(size_t)), 0,
	    "Unexpected mallctl failure while resetting profile data");
	assert_zu_eq(lg_prof_sample, get_lg_prof_sample(),
	    "Expected profile sample rate change");
}