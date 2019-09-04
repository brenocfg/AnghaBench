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
struct address {int sortkey; } ;

/* Variables and functions */

__attribute__((used)) static int addrcmp(const void *_a, const void *_b)
{
	const struct address *a = _a, *b = _b;
	return b->sortkey - a->sortkey;
}