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
struct pstore {int /*<<< orphan*/ * header_area; int /*<<< orphan*/ * zero_area; int /*<<< orphan*/ * area; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_area(struct pstore *ps)
{
	if (ps->area)
		vfree(ps->area);
	ps->area = NULL;

	if (ps->zero_area)
		vfree(ps->zero_area);
	ps->zero_area = NULL;

	if (ps->header_area)
		vfree(ps->header_area);
	ps->header_area = NULL;
}