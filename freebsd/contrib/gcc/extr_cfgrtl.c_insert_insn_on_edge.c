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
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_2__* edge ;
struct TYPE_5__ {scalar_t__ r; } ;
struct TYPE_6__ {int flags; TYPE_1__ insns; } ;

/* Variables and functions */
 int EDGE_ABNORMAL ; 
 scalar_t__ EDGE_CRITICAL_P (TYPE_2__*) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  push_to_sequence (scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 

void
insert_insn_on_edge (rtx pattern, edge e)
{
  /* We cannot insert instructions on an abnormal critical edge.
     It will be easier to find the culprit if we die now.  */
  gcc_assert (!((e->flags & EDGE_ABNORMAL) && EDGE_CRITICAL_P (e)));

  if (e->insns.r == NULL_RTX)
    start_sequence ();
  else
    push_to_sequence (e->insns.r);

  emit_insn (pattern);

  e->insns.r = get_insns ();
  end_sequence ();
}