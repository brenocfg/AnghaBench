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
struct queue_elem {int lineno; int /*<<< orphan*/  filename; int /*<<< orphan*/  data; struct queue_elem* next; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  DEFINE_EXPAND 132 
#define  DEFINE_INSN 131 
#define  DEFINE_PEEPHOLE 130 
#define  DEFINE_PEEPHOLE2 129 
#define  DEFINE_SPLIT 128 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int) ; 
 struct queue_elem* define_attr_queue ; 
 struct queue_elem* define_insn_queue ; 
 struct queue_elem* define_pred_queue ; 
 int /*<<< orphan*/  free (struct queue_elem*) ; 
 int /*<<< orphan*/  insn_elision ; 
 int /*<<< orphan*/  maybe_eval_c_test (int /*<<< orphan*/ ) ; 
 struct queue_elem* other_queue ; 
 int /*<<< orphan*/  read_rtx_filename ; 
 int /*<<< orphan*/  record_insn_name (int,int /*<<< orphan*/ ) ; 
 int sequence_num ; 

rtx
read_md_rtx (int *lineno, int *seqnr)
{
  struct queue_elem **queue, *elem;
  rtx desc;

 discard:

  /* Read all patterns from a given queue before moving on to the next.  */
  if (define_attr_queue != NULL)
    queue = &define_attr_queue;
  else if (define_pred_queue != NULL)
    queue = &define_pred_queue;
  else if (define_insn_queue != NULL)
    queue = &define_insn_queue;
  else if (other_queue != NULL)
    queue = &other_queue;
  else
    return NULL_RTX;

  elem = *queue;
  *queue = elem->next;
  desc = elem->data;
  read_rtx_filename = elem->filename;
  *lineno = elem->lineno;
  *seqnr = sequence_num;

  free (elem);

  /* Discard insn patterns which we know can never match (because
     their C test is provably always false).  If insn_elision is
     false, our caller needs to see all the patterns.  Note that the
     elided patterns are never counted by the sequence numbering; it
     it is the caller's responsibility, when insn_elision is false, not
     to use elided pattern numbers for anything.  */
  switch (GET_CODE (desc))
    {
    case DEFINE_INSN:
    case DEFINE_EXPAND:
      if (maybe_eval_c_test (XSTR (desc, 2)) != 0)
	sequence_num++;
      else if (insn_elision)
	goto discard;

      /* *seqnr is used here so the name table will match caller's
	 idea of insn numbering, whether or not elision is active.  */
      record_insn_name (*seqnr, XSTR (desc, 0));
      break;

    case DEFINE_SPLIT:
    case DEFINE_PEEPHOLE:
    case DEFINE_PEEPHOLE2:
      if (maybe_eval_c_test (XSTR (desc, 1)) != 0)
	sequence_num++;
      else if (insn_elision)
	    goto discard;
      break;

    default:
      break;
    }

  return desc;
}