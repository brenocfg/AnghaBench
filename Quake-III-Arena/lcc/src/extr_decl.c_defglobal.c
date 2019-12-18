#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* global ) (TYPE_2__*) ;int /*<<< orphan*/  (* export ) (TYPE_2__*) ;} ;
struct TYPE_7__ {int seg; } ;
struct TYPE_8__ {scalar_t__ sclass; int defined; TYPE_1__ u; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 TYPE_6__* IR ; 
 scalar_t__ STATIC ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  swtoseg (int) ; 

void defglobal(Symbol p, int seg) {
	p->u.seg = seg;
	swtoseg(p->u.seg);
	if (p->sclass != STATIC)
		(*IR->export)(p);
	(*IR->global)(p);
	p->defined = 1;
}