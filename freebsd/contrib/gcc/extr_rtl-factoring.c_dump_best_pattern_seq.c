#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* matching_seq ;
struct TYPE_4__ {int gain; int abstracted_length; int /*<<< orphan*/  link_reg; TYPE_1__* matching_seqs; int /*<<< orphan*/  insn; } ;
struct TYPE_3__ {int abstracted_length; struct TYPE_3__* next_matching_seq; int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* pattern_seqs ; 

__attribute__((used)) static void
dump_best_pattern_seq (int iter)
{
  matching_seq mseq;

  if (!dump_file)
    return;

  fprintf (dump_file, ";; Iteration %d\n", iter);
  fprintf (dump_file,
           "Best pattern sequence with %d gain is at insn %d (length %d).\n",
           pattern_seqs->gain, INSN_UID (pattern_seqs->insn),
           pattern_seqs->abstracted_length);
  fprintf (dump_file, "Matching sequences are at");
  for (mseq = pattern_seqs->matching_seqs; mseq;
       mseq = mseq->next_matching_seq)
    {
      fprintf (dump_file, " insn %d (length %d)", INSN_UID (mseq->insn),
               mseq->abstracted_length);
      if (mseq->next_matching_seq)
        fprintf (dump_file, ",");
    }
  fprintf (dump_file, ".\n");
  fprintf (dump_file, "Using reg %d as link register.\n\n",
           REGNO (pattern_seqs->link_reg));
}