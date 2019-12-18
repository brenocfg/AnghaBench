#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* x; struct TYPE_6__* link; } ;
typedef  TYPE_1__* List ;

/* Variables and functions */
 int /*<<< orphan*/  NEW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 TYPE_1__* freenodes ; 

List append(void *x, List list) {
	List new;

	if ((new = freenodes) != NULL)
		freenodes = freenodes->link;
	else
		NEW(new, PERM);
	if (list) {
		new->link = list->link;
		list->link = new;
	} else
		new->link = new;
	new->x = x;
	return new;
}