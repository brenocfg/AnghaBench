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
typedef  int /*<<< orphan*/  sbitmap ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 int EDGE_ABNORMAL ; 
 int EDGE_ABNORMAL_CALL ; 
 int EDGE_EH ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  free_INSN_LIST_list (scalar_t__*) ; 
 int /*<<< orphan*/  make_label_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ reachable_handlers (scalar_t__) ; 

void
rtl_make_eh_edge (sbitmap edge_cache, basic_block src, rtx insn)
{
  int is_call = CALL_P (insn) ? EDGE_ABNORMAL_CALL : 0;
  rtx handlers, i;

  handlers = reachable_handlers (insn);

  for (i = handlers; i; i = XEXP (i, 1))
    make_label_edge (edge_cache, src, XEXP (i, 0),
		     EDGE_ABNORMAL | EDGE_EH | is_call);

  free_INSN_LIST_list (&handlers);
}