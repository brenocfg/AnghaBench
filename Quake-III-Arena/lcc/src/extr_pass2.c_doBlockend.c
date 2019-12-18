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
typedef  int /*<<< orphan*/  rcc_interface_ty ;
struct TYPE_7__ {struct TYPE_7__* prev; int /*<<< orphan*/  begin; } ;
struct TYPE_5__ {int /*<<< orphan*/  begin; } ;
struct TYPE_6__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  Blockend ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 TYPE_3__* blockstack ; 
 TYPE_2__* code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exitscope () ; 

__attribute__((used)) static void doBlockend(rcc_interface_ty in) {
	assert(blockstack);
	code(Blockend)->u.begin = blockstack->begin;
	blockstack = blockstack->prev;
	exitscope();
}