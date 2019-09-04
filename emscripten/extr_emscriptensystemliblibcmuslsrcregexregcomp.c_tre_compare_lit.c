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
struct TYPE_2__ {int code_min; } ;
typedef  TYPE_1__ tre_literal_t ;

/* Variables and functions */

__attribute__((used)) static int
tre_compare_lit(const void *a, const void *b)
{
	const tre_literal_t *const *la = a;
	const tre_literal_t *const *lb = b;
	/* assumes the range of valid code_min is < INT_MAX */
	return la[0]->code_min - lb[0]->code_min;
}