#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* pattern_seq ;
typedef  TYPE_2__* matching_seq ;
struct TYPE_7__ {scalar_t__ insn; int matching_length; int cost; struct TYPE_7__* next_matching_seq; } ;
struct TYPE_6__ {scalar_t__ insn; struct TYPE_6__* next_pattern_seq; scalar_t__ gain; TYPE_2__* matching_seqs; } ;

/* Variables and functions */
 scalar_t__ compute_rtx_cost (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  free_pattern_seq (TYPE_1__*) ; 
 TYPE_1__* pattern_seqs ; 
 scalar_t__ prev_insn_in_block (scalar_t__) ; 
 int seq_call_cost ; 

__attribute__((used)) static void
erase_from_pattern_seqs (rtx insn, int len)
{
  pattern_seq *pseq;
  matching_seq *mseq;
  rtx x;
  int plen, mlen;
  int pcost, mcost;

  while (len > 0)
    {
      for (pseq = &pattern_seqs; *pseq;)
        {
          plen = 0;
          pcost = 0;
          for (x = (*pseq)->insn; x && (x != insn);
               x = prev_insn_in_block (x))
            {
              plen++;
              pcost += compute_rtx_cost (x);
            }

          if (pcost <= seq_call_cost)
            {
              pattern_seq temp = *pseq;
              *pseq = temp->next_pattern_seq;
              free_pattern_seq (temp);
            }
          else
            {
              for (mseq = &(*pseq)->matching_seqs; *mseq;)
                {
                  mlen = 0;
                  mcost = 0;
                  for (x = (*mseq)->insn;
                       x && (x != insn) && (mlen < plen)
                       && (mlen < (*mseq)->matching_length);
                       x = prev_insn_in_block (x))
                    {
                      mlen++;
                      mcost += compute_rtx_cost (x);
                    }

                  if (mcost <= seq_call_cost)
                    {
                      matching_seq temp = *mseq;
                      *mseq = temp->next_matching_seq;
                      free (temp);
                      /* Set to 0 to force gain recomputation.  */
                      (*pseq)->gain = 0;
                    }
                  else
                    {
                      if (mlen < (*mseq)->matching_length)
                        {
                          (*mseq)->cost = mcost;
                          (*mseq)->matching_length = mlen;
                          /* Set to 0 to force gain recomputation.  */
                          (*pseq)->gain = 0;
                        }
                      mseq = &(*mseq)->next_matching_seq;
                    }
                }

              pseq = &(*pseq)->next_pattern_seq;
            }
        }

      len--;
      insn = prev_insn_in_block (insn);
    }
}