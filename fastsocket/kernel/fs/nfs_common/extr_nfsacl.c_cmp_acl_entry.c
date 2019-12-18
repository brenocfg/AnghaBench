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
struct posix_acl_entry {scalar_t__ e_tag; scalar_t__ e_id; } ;

/* Variables and functions */

__attribute__((used)) static int
cmp_acl_entry(const void *x, const void *y)
{
	const struct posix_acl_entry *a = x, *b = y;

	if (a->e_tag != b->e_tag)
		return a->e_tag - b->e_tag;
	else if (a->e_id > b->e_id)
		return 1;
	else if (a->e_id < b->e_id)
		return -1;
	else
		return 0;
}