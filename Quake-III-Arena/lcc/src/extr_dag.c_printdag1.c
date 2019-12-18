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
struct TYPE_5__ {struct TYPE_5__** kids; } ;
typedef  TYPE_1__* Node ;

/* Variables and functions */
 int NELEMS (TYPE_1__**) ; 
 int nodeid (int /*<<< orphan*/ ) ; 
 int* printed (int) ; 
 int /*<<< orphan*/  printnode (TYPE_1__*,int,int) ; 

__attribute__((used)) static void printdag1(Node p, int fd, int lev) {
	int id, i;

	if (p == 0 || *printed(id = nodeid((Tree)p)))
		return;
	*printed(id) = 1;
	for (i = 0; i < NELEMS(p->kids); i++)
		printdag1(p->kids[i], fd, lev + 1);
	printnode(p, fd, lev);
}