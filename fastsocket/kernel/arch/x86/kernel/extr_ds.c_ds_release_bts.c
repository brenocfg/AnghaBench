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
struct bts_tracer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_free_bts (struct bts_tracer*) ; 
 int /*<<< orphan*/  ds_suspend_bts (struct bts_tracer*) ; 
 int /*<<< orphan*/  might_sleep () ; 

void ds_release_bts(struct bts_tracer *tracer)
{
	might_sleep();

	if (!tracer)
		return;

	ds_suspend_bts(tracer);
	ds_free_bts(tracer);
}