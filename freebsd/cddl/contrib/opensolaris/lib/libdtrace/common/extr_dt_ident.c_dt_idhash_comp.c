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
struct TYPE_2__ {scalar_t__ di_id; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_1__ dt_ident_t ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_idhash_comp(const void *lp, const void *rp)
{
	const dt_ident_t *lhs = *((const dt_ident_t **)lp);
	const dt_ident_t *rhs = *((const dt_ident_t **)rp);

	if (lhs->di_id != rhs->di_id)
		return ((int)(lhs->di_id - rhs->di_id));
	else
		return (strcmp(lhs->di_name, rhs->di_name));
}