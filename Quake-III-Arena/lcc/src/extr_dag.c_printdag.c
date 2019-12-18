#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tree ;
struct TYPE_5__ {struct TYPE_5__* link; } ;
typedef  TYPE_1__* Node ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* forest ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodeid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printdag1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__* printed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

void printdag(Node p, int fd) {
	FILE *f = fd == 1 ? stdout : stderr;

	printed(0);
	if (p == 0) {
		if ((p = forest) != NULL)
			do {
				p = p->link;
				printdag1(p, fd, 0);
			} while (p != forest);
	} else if (*printed(nodeid((Tree)p)))
		fprint(f, "node'%d printed above\n", nodeid((Tree)p));
	else
		printdag1(p, fd, 0);
}