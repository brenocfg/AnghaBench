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
typedef  int /*<<< orphan*/ * Tree ;
struct TYPE_2__ {scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  Swtch ;
typedef  int /*<<< orphan*/  Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 int /*<<< orphan*/  branch (int) ; 
 int /*<<< orphan*/  conditional ; 
 int /*<<< orphan*/  definelab (int) ; 
 int /*<<< orphan*/  definept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* findlabel (int) ; 
 int /*<<< orphan*/  gettok () ; 
 double refinc ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  statement (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/ * texpr (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void whilestmt(int lab, Swtch swp, int lev) {
	Coordinate pt;
	Tree e;

	refinc *= 10.0;
	t = gettok();
	expect('(');
	walk(NULL, 0, 0);
	pt = src;
	e = texpr(conditional, ')', FUNC);
	branch(lab + 1);
	definelab(lab);
	statement(lab, swp, lev);
	definelab(lab + 1);
	definept(&pt);
	walk(e, lab, 0);
	if (findlabel(lab + 2)->ref)
		definelab(lab + 2);
}