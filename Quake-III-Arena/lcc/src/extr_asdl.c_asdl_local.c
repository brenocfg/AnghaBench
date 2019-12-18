#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* next; scalar_t__ cse; } ;
struct TYPE_11__ {TYPE_2__ t; } ;
struct TYPE_9__ {scalar_t__ offset; } ;
struct TYPE_12__ {TYPE_3__ u; scalar_t__ temporary; TYPE_1__ x; } ;
typedef  TYPE_4__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mk_symbol (TYPE_4__*) ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Local (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symboluid (TYPE_4__*) ; 
 TYPE_4__* temps ; 

__attribute__((used)) static void asdl_local(Symbol p) {
	assert(p->x.offset == 0);
	put(rcc_Local(symboluid(p), mk_symbol(p)));
	if (p->temporary && p->u.t.cse) {
		p->u.t.next = temps;
		temps = p;
	}
}