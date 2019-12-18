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
struct shadow_spine {int count; int /*<<< orphan*/ * nodes; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int unlock_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int exit_shadow_spine(struct shadow_spine *s)
{
	int r = 0, i;

	for (i = 0; i < s->count; i++) {
		int r2 = unlock_block(s->info, s->nodes[i]);
		if (r2 < 0)
			r = r2;
	}

	return r;
}