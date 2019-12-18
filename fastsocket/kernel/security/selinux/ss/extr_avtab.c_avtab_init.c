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
struct avtab {scalar_t__ nel; int /*<<< orphan*/ * htable; } ;

/* Variables and functions */

int avtab_init(struct avtab *h)
{
	h->htable = NULL;
	h->nel = 0;
	return 0;
}