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
struct expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_OR ; 
 struct expr* expr_eliminate_yn (struct expr*) ; 
 int /*<<< orphan*/  expr_extract_eq (int /*<<< orphan*/ ,struct expr**,struct expr**,struct expr**) ; 

struct expr *expr_extract_eq_or(struct expr **ep1, struct expr **ep2)
{
	struct expr *tmp = NULL;
	expr_extract_eq(E_OR, &tmp, ep1, ep2);
	if (tmp) {
		*ep1 = expr_eliminate_yn(*ep1);
		*ep2 = expr_eliminate_yn(*ep2);
	}
	return tmp;
}