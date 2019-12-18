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
struct expr {int type; } ;

/* Variables and functions */
#define  E_AND 129 
#define  E_OR 128 
 int /*<<< orphan*/  expr_eliminate_dups1 (int,struct expr**,struct expr**) ; 
 int /*<<< orphan*/  expr_eliminate_dups2 (int,struct expr**,struct expr**) ; 
 struct expr* expr_eliminate_yn (struct expr*) ; 
 int trans_count ; 

struct expr *expr_eliminate_dups(struct expr *e)
{
	int oldcount;
	if (!e)
		return e;

	oldcount = trans_count;
	while (1) {
		trans_count = 0;
		switch (e->type) {
		case E_OR: case E_AND:
			expr_eliminate_dups1(e->type, &e, &e);
			expr_eliminate_dups2(e->type, &e, &e);
		default:
			;
		}
		if (!trans_count)
			break;
		e = expr_eliminate_yn(e);
	}
	trans_count = oldcount;
	return e;
}