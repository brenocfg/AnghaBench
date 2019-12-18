#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  ce_info ;
struct TYPE_21__ {int pass; TYPE_3__* test_bb; int /*<<< orphan*/  else_bb; int /*<<< orphan*/  then_bb; } ;
typedef  TYPE_2__ ce_if_block_t ;
typedef  TYPE_3__* basic_block ;
struct TYPE_22__ {int /*<<< orphan*/  succs; } ;
struct TYPE_20__ {int flags; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 size_t CDI_POST_DOMINATORS ; 
 scalar_t__ DOM_NO_FAST_QUERY ; 
 int EDGE_COMPLEX ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int EDGE_FALLTHRU ; 
 int EDGE_LOOP_EXIT ; 
 TYPE_1__* EDGE_SUCC (TYPE_3__*,int) ; 
 int /*<<< orphan*/  HAVE_conditional_execution ; 
 scalar_t__ HAVE_conditional_trap ; 
 scalar_t__ HAVE_trap ; 
 int /*<<< orphan*/  IFCVT_INIT_EXTRA_FIELDS (TYPE_2__*) ; 
 scalar_t__* dom_computed ; 
 scalar_t__ dump_file ; 
 scalar_t__ find_cond_trap (TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ find_if_block (TYPE_2__*) ; 
 scalar_t__ find_if_case_1 (TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ find_if_case_2 (TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 scalar_t__ reload_completed ; 

__attribute__((used)) static basic_block
find_if_header (basic_block test_bb, int pass)
{
  ce_if_block_t ce_info;
  edge then_edge;
  edge else_edge;

  /* The kind of block we're looking for has exactly two successors.  */
  if (EDGE_COUNT (test_bb->succs) != 2)
    return NULL;

  then_edge = EDGE_SUCC (test_bb, 0);
  else_edge = EDGE_SUCC (test_bb, 1);

  /* Neither edge should be abnormal.  */
  if ((then_edge->flags & EDGE_COMPLEX)
      || (else_edge->flags & EDGE_COMPLEX))
    return NULL;

  /* Nor exit the loop.  */
  if ((then_edge->flags & EDGE_LOOP_EXIT)
      || (else_edge->flags & EDGE_LOOP_EXIT))
    return NULL;

  /* The THEN edge is canonically the one that falls through.  */
  if (then_edge->flags & EDGE_FALLTHRU)
    ;
  else if (else_edge->flags & EDGE_FALLTHRU)
    {
      edge e = else_edge;
      else_edge = then_edge;
      then_edge = e;
    }
  else
    /* Otherwise this must be a multiway branch of some sort.  */
    return NULL;

  memset (&ce_info, '\0', sizeof (ce_info));
  ce_info.test_bb = test_bb;
  ce_info.then_bb = then_edge->dest;
  ce_info.else_bb = else_edge->dest;
  ce_info.pass = pass;

#ifdef IFCVT_INIT_EXTRA_FIELDS
  IFCVT_INIT_EXTRA_FIELDS (&ce_info);
#endif

  if (find_if_block (&ce_info))
    goto success;

  if (HAVE_trap && HAVE_conditional_trap
      && find_cond_trap (test_bb, then_edge, else_edge))
    goto success;

  if (dom_computed[CDI_POST_DOMINATORS] >= DOM_NO_FAST_QUERY
      && (! HAVE_conditional_execution || reload_completed))
    {
      if (find_if_case_1 (test_bb, then_edge, else_edge))
	goto success;
      if (find_if_case_2 (test_bb, then_edge, else_edge))
	goto success;
    }

  return NULL;

 success:
  if (dump_file)
    fprintf (dump_file, "Conversion succeeded on pass %d.\n", pass);
  return ce_info.test_bb;
}