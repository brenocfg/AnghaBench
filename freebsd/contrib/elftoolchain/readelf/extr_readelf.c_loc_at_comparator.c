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
struct loc_at {scalar_t__ la_off; } ;

/* Variables and functions */

__attribute__((used)) static int
loc_at_comparator(const void *la1, const void *la2)
{
	const struct loc_at *left, *right;

	left = (const struct loc_at *)la1;
	right = (const struct loc_at *)la2;

	if (left->la_off > right->la_off)
		return (1);
	else if (left->la_off < right->la_off)
		return (-1);
	else
		return (0);
}