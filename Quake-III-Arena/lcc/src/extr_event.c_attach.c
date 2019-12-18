#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct entry {void* cl; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Apply ;

/* Variables and functions */
 int /*<<< orphan*/  NEW (struct entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  append (struct entry*,int /*<<< orphan*/ ) ; 

void attach(Apply func, void *cl, List *list) {
	struct entry *p;

	NEW(p, PERM);
	p->func = func;
	p->cl = cl;
	*list = append(p, *list);
}