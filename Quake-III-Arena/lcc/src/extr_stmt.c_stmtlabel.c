#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  label; } ;
struct TYPE_7__ {TYPE_1__ l; } ;
struct TYPE_8__ {char src; int defined; TYPE_2__ u; int /*<<< orphan*/  name; int /*<<< orphan*/  scope; } ;
typedef  TYPE_3__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 int /*<<< orphan*/  LABELS ; 
 int /*<<< orphan*/  definelab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  genlabel (int) ; 
 int /*<<< orphan*/  gettok () ; 
 TYPE_3__* install (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char src ; 
 int /*<<< orphan*/  stmtlabs ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  token ; 

__attribute__((used)) static void stmtlabel(void) {
	Symbol p = lookup(token, stmtlabs);

	if (p == NULL) {
		p = install(token, &stmtlabs, 0, FUNC);
		p->scope = LABELS;
		p->u.l.label = genlabel(1);
		p->src = src;
	}
	if (p->defined)
		error("redefinition of label `%s' previously defined at %w\n", p->name, &p->src);

	p->defined = 1;
	definelab(p->u.l.label);
	t = gettok();
	expect(':');
}