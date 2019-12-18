#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* regnode; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int number; int mask; int set; TYPE_1__ x; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  NEW0 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  stringf (char*,int) ; 

Symbol mkreg(char *fmt, int n, int mask, int set) {
	Symbol p;

	NEW0(p, PERM);
	p->name = p->x.name = stringf(fmt, n);
	NEW0(p->x.regnode, PERM);
	p->x.regnode->number = n;
	p->x.regnode->mask = mask<<n;
	p->x.regnode->set = set;
	return p;
}