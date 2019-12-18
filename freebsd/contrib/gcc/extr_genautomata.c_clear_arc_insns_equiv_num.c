#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  state_t ;
typedef  TYPE_3__* arc_t ;
struct TYPE_9__ {TYPE_2__* insn; } ;
struct TYPE_8__ {TYPE_1__* insn_reserv_decl; } ;
struct TYPE_7__ {scalar_t__ equiv_class_num; } ;

/* Variables and functions */
 TYPE_3__* first_out_arc (int /*<<< orphan*/ ) ; 
 TYPE_3__* next_out_arc (TYPE_3__*) ; 

__attribute__((used)) static void
clear_arc_insns_equiv_num (state_t state)
{
  arc_t arc;

  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    arc->insn->insn_reserv_decl->equiv_class_num = 0;
}