#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* stabtype ) (TYPE_1__*) ;} ;
struct TYPE_5__ {scalar_t__ sclass; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 TYPE_4__* IR ; 
 scalar_t__ TYPEDEF ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void typestab(Symbol p, void *cl) {
	if (*(Symbol *)cl == 0 && p->sclass && p->sclass != TYPEDEF)
		*(Symbol *)cl = p;
	if ((p->sclass == TYPEDEF || p->sclass == 0) && IR->stabtype)
		(*IR->stabtype)(p);
}