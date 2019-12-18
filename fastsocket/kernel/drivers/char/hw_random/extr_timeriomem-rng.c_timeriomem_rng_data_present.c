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
struct hwrng {scalar_t__ priv; } ;
struct TYPE_2__ {int present; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 TYPE_1__* timeriomem_rng_data ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timeriomem_rng_data_present(struct hwrng *rng, int wait)
{
	if (rng->priv == 0)
		return 1;

	if (!wait || timeriomem_rng_data->present)
		return timeriomem_rng_data->present;

	wait_for_completion(&timeriomem_rng_data->completion);

	return 1;
}