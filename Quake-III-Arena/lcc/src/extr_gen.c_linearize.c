#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* prev; TYPE_2__** kids; } ;
struct TYPE_10__ {TYPE_1__ x; } ;
typedef  TYPE_2__* Node ;

/* Variables and functions */
 int NELEMS (TYPE_2__**) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  relink (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void linearize(Node p, Node next) {
	int i;

	for (i = 0; i < NELEMS(p->x.kids) && p->x.kids[i]; i++)
		linearize(p->x.kids[i], next);
	relink(next->x.prev, p);
	relink(p, next);
	debug(fprint(stderr, "(listing %x)\n", p));
}