#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* al_valfree ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* al_namefree ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ alist_t ;
struct TYPE_5__ {int /*<<< orphan*/  ale_name; } ;
typedef  TYPE_2__ alist_el_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alist_free_cb(void *arg1, void *arg2)
{
	alist_el_t *el = arg1;
	alist_t *alist = arg2;
	if (alist->al_namefree)
		alist->al_namefree(el->ale_name);
	if (alist->al_valfree)
		alist->al_valfree(el->ale_name);
	free(el);
}