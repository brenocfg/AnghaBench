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
struct TYPE_2__ {int present; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__* timeriomem_rng_data ; 

__attribute__((used)) static void timeriomem_rng_trigger(unsigned long dummy)
{
	timeriomem_rng_data->present = 1;
	complete(&timeriomem_rng_data->completion);
}