#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_1__* regnode; } ;
struct TYPE_7__ {TYPE_2__ x; } ;
struct TYPE_5__ {size_t set; int /*<<< orphan*/  mask; } ;
typedef  TYPE_3__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpregs (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freemask ; 

__attribute__((used)) static void putreg(Symbol r) {
	assert(r && r->x.regnode);
	freemask[r->x.regnode->set] |= r->x.regnode->mask;
	debug(dumpregs("(freeing %s)\n", r->x.name, NULL));
}