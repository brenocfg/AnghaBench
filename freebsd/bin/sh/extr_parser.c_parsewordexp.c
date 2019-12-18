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
struct TYPE_2__ {union node* next; } ;
union node {TYPE_1__ narg; } ;

/* Variables and functions */
 int TEOF ; 
 int TWORD ; 
 scalar_t__ checkkwd ; 
 scalar_t__ doprompt ; 
 int /*<<< orphan*/ * heredoclist ; 
 union node* makename () ; 
 scalar_t__ needprompt ; 
 int /*<<< orphan*/  parser_temp_free_all () ; 
 int readtoken () ; 
 int /*<<< orphan*/  setprompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synexpect (int) ; 
 scalar_t__ tokpushback ; 

union node *
parsewordexp(void)
{
	union node *n, *first = NULL, **pnext;
	int t;

	/* This assumes the parser is not re-entered,
	 * which could happen if we add command substitution on PS1/PS2.
	 */
	parser_temp_free_all();
	heredoclist = NULL;

	tokpushback = 0;
	checkkwd = 0;
	doprompt = 0;
	setprompt(0);
	needprompt = 0;
	pnext = &first;
	while ((t = readtoken()) != TEOF) {
		if (t != TWORD)
			synexpect(TWORD);
		n = makename();
		*pnext = n;
		pnext = &n->narg.next;
	}
	return first;
}