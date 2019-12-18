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
struct poll_delay_t {int min; int max; } ;

/* Variables and functions */

__attribute__((used)) static struct poll_delay_t poll_delay_min_max(int min, int max)
{
	struct poll_delay_t result;

	result.min = min;
	result.max = max;
	return result;
}