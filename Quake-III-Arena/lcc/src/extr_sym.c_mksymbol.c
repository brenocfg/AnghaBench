#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_8__ {int /*<<< orphan*/  (* defsymbol ) (TYPE_1__*) ;} ;
struct TYPE_7__ {int sclass; int defined; int /*<<< orphan*/  type; int /*<<< orphan*/  scope; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int EXTERN ; 
 int /*<<< orphan*/  GLOBAL ; 
 TYPE_6__* IR ; 
 int /*<<< orphan*/  NEW0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  globals ; 
 TYPE_1__* install (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

Symbol mksymbol(int sclass, const char *name, Type ty) {
	Symbol p;

	if (sclass == EXTERN)
		p = install(string(name), &globals, GLOBAL, PERM);
	else {
		NEW0(p, PERM);
		p->name = string(name);
		p->scope = GLOBAL;
	}
	p->sclass = sclass;
	p->type = ty;
	(*IR->defsymbol)(p);
	p->defined = 1;
	return p;
}