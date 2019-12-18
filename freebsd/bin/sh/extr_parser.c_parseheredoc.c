#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union node {int dummy; } node ;
struct heredoc {TYPE_2__* here; int /*<<< orphan*/  striptabs; int /*<<< orphan*/  eofmark; struct heredoc* next; } ;
struct TYPE_3__ {union node* doc; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ nhere; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQSYNTAX ; 
 scalar_t__ NHERE ; 
 int /*<<< orphan*/  SQSYNTAX ; 
 struct heredoc* heredoclist ; 
 union node* makename () ; 
 scalar_t__ needprompt ; 
 int /*<<< orphan*/  pgetc () ; 
 int /*<<< orphan*/  readtoken1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprompt (int) ; 

__attribute__((used)) static void
parseheredoc(void)
{
	struct heredoc *here;
	union node *n;

	while (heredoclist) {
		here = heredoclist;
		heredoclist = here->next;
		if (needprompt) {
			setprompt(2);
			needprompt = 0;
		}
		readtoken1(pgetc(), here->here->type == NHERE? SQSYNTAX : DQSYNTAX,
				here->eofmark, here->striptabs);
		n = makename();
		here->here->nhere.doc = n;
	}
}