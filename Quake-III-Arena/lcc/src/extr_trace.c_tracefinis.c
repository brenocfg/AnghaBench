#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Tree ;
struct TYPE_11__ {TYPE_4__* loc; } ;
struct TYPE_12__ {TYPE_1__ c; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; TYPE_2__ u; } ;
struct TYPE_13__ {struct TYPE_13__** kids; } ;
typedef  TYPE_4__* Symbol ;

/* Variables and functions */
 scalar_t__ ARG ; 
 scalar_t__ P ; 
 TYPE_3__* args ; 
 int /*<<< orphan*/  calltree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  charptype ; 
 int /*<<< orphan*/  fmt ; 
 scalar_t__* fmtend ; 
 scalar_t__* fp ; 
 int /*<<< orphan*/  freturn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idtree (TYPE_4__*) ; 
 TYPE_4__* mkstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string (int /*<<< orphan*/ ) ; 
 TYPE_3__* tree (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracefinis(Symbol printer) {
	Tree *ap;
	Symbol p;

	*fp = 0;
	p = mkstr(string(fmt));
	for (ap = &args; *ap; ap = &(*ap)->kids[1])
		;
	*ap = tree(ARG+P, charptype, pointer(idtree(p->u.c.loc)), 0);
	walk(calltree(pointer(idtree(printer)), freturn(printer->type), args, NULL), 0, 0);
	args = 0;
	fp = fmtend = 0;
}