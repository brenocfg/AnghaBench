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
struct TYPE_2__ {scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  Swtch ;

/* Variables and functions */
 char WHILE ; 
 int /*<<< orphan*/  conditional (char) ; 
 int /*<<< orphan*/  definelab (int) ; 
 int /*<<< orphan*/  definept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* findlabel (int) ; 
 int /*<<< orphan*/  gettok () ; 
 double refinc ; 
 int /*<<< orphan*/  statement (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dostmt(int lab, Swtch swp, int lev) {
	refinc *= 10.0;
	t = gettok();
	definelab(lab);
	statement(lab, swp, lev);
	definelab(lab + 1);
	expect(WHILE);
	expect('(');
	definept(NULL);
	walk(conditional(')'), lab, 0);
	if (findlabel(lab + 2)->ref)
		definelab(lab + 2);
}