#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_block_def {int dummy; } ;
typedef  TYPE_1__* seq_block ;
typedef  TYPE_2__* matching_seq ;
struct TYPE_7__ {TYPE_2__* matching_seqs; } ;
struct TYPE_6__ {scalar_t__ cost; scalar_t__ abstracted_length; struct TYPE_6__* next_matching_seq; } ;
struct TYPE_5__ {scalar_t__ length; TYPE_2__* matching_seqs; struct TYPE_5__* next_seq_block; void* label; } ;

/* Variables and functions */
 void* NULL_RTX ; 
 TYPE_4__* pattern_seqs ; 
 TYPE_1__* seq_blocks ; 
 scalar_t__ seq_call_cost ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
determine_seq_blocks (void)
{
  seq_block sb;
  matching_seq *mseq;
  matching_seq m;

  /* Initialize SEQ_BLOCKS to empty.  */
  seq_blocks = 0;

  /* Process all matching sequences.  */
  for (mseq = &pattern_seqs->matching_seqs; *mseq;)
    {
      /* Deal only with matching sequences being long enough. */
      if ((*mseq)->cost <= seq_call_cost)
        {
          mseq = &(*mseq)->next_matching_seq;
          continue;
        }

      /* Ensure that SB contains a seq_block with the appropriate length.
         Insert a new seq_block if necessary.  */
      if (!seq_blocks || ((*mseq)->abstracted_length < seq_blocks->length))
        {
          sb = (seq_block) xmalloc (sizeof (struct seq_block_def));
          sb->length = (*mseq)->abstracted_length;
          sb->label = NULL_RTX;
          sb->matching_seqs = 0;
          sb->next_seq_block = seq_blocks;
          seq_blocks = sb;
        }
      else
        {
          for (sb = seq_blocks; sb; sb = sb->next_seq_block)
            {
              if ((*mseq)->abstracted_length == sb->length)
                break;
              if (!sb->next_seq_block
                  || ((*mseq)->abstracted_length <
                      sb->next_seq_block->length))
                {
                  seq_block temp =
                    (seq_block) xmalloc (sizeof (struct seq_block_def));
                  temp->length = (*mseq)->abstracted_length;
                  temp->label = NULL_RTX;
                  temp->matching_seqs = 0;
                  temp->next_seq_block = sb->next_seq_block;
                  sb->next_seq_block = temp;
                }
            }
        }

      /* Remove the matching sequence from the linked list of the pattern
         sequence and link it to SB.  */
      m = *mseq;
      *mseq = m->next_matching_seq;
      m->next_matching_seq = sb->matching_seqs;
      sb->matching_seqs = m;
    }
}