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
struct coal_sort_s {int usr_order; } ;

/* Variables and functions */

__attribute__((used)) static int usr_asc_cmp(const void *a, const void *b)
{
	const struct coal_sort_s *csA = (const struct coal_sort_s *)a;
	const struct coal_sort_s *csB = (const struct coal_sort_s *)b;

	return (csA->usr_order - csB->usr_order);
}