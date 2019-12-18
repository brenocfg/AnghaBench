#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnsttree (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  eqtree (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idtree (TYPE_1__*) ; 
 int /*<<< orphan*/  listnodes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signedint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmp(int op, Symbol p, long n, int lab) {
	Type ty = signedint(p->type);

	listnodes(eqtree(op,
			cast(idtree(p), ty),
			cnsttree(ty, n)),
		lab, 0);
}