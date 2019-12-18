#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_8__ {struct TYPE_8__* next_bb; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; TYPE_2__* src; } ;

/* Variables and functions */
 scalar_t__ BB_END (TYPE_2__*) ; 
 scalar_t__ BB_HEAD (TYPE_2__*) ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ any_condjump_p (scalar_t__) ; 
 scalar_t__ any_uncondjump_p (scalar_t__) ; 
 int /*<<< orphan*/  delete_insn_chain (scalar_t__,scalar_t__) ; 
 scalar_t__ only_sets_cc0_p (scalar_t__) ; 
 scalar_t__ onlyjump_p (scalar_t__) ; 
 scalar_t__ single_succ_p (TYPE_2__*) ; 

__attribute__((used)) static void
rtl_tidy_fallthru_edge (edge e)
{
  rtx q;
  basic_block b = e->src, c = b->next_bb;

  /* ??? In a late-running flow pass, other folks may have deleted basic
     blocks by nopping out blocks, leaving multiple BARRIERs between here
     and the target label. They ought to be chastised and fixed.

     We can also wind up with a sequence of undeletable labels between
     one block and the next.

     So search through a sequence of barriers, labels, and notes for
     the head of block C and assert that we really do fall through.  */

  for (q = NEXT_INSN (BB_END (b)); q != BB_HEAD (c); q = NEXT_INSN (q))
    if (INSN_P (q))
      return;

  /* Remove what will soon cease being the jump insn from the source block.
     If block B consisted only of this single jump, turn it into a deleted
     note.  */
  q = BB_END (b);
  if (JUMP_P (q)
      && onlyjump_p (q)
      && (any_uncondjump_p (q)
	  || single_succ_p (b)))
    {
#ifdef HAVE_cc0
      /* If this was a conditional jump, we need to also delete
	 the insn that set cc0.  */
      if (any_condjump_p (q) && only_sets_cc0_p (PREV_INSN (q)))
	q = PREV_INSN (q);
#endif

      q = PREV_INSN (q);

      /* We don't want a block to end on a line-number note since that has
	 the potential of changing the code between -g and not -g.  */
      while (NOTE_P (q) && NOTE_LINE_NUMBER (q) >= 0)
	q = PREV_INSN (q);
    }

  /* Selectively unlink the sequence.  */
  if (q != PREV_INSN (BB_HEAD (c)))
    delete_insn_chain (NEXT_INSN (q), PREV_INSN (BB_HEAD (c)));

  e->flags |= EDGE_FALLTHRU;
}