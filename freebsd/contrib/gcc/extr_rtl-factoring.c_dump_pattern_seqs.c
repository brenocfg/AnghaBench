#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pattern_seq ;
typedef  TYPE_2__* matching_seq ;
struct TYPE_5__ {int matching_length; struct TYPE_5__* next_matching_seq; int /*<<< orphan*/  insn; } ;
struct TYPE_4__ {TYPE_2__* matching_seqs; int /*<<< orphan*/  insn; struct TYPE_4__* next_pattern_seq; } ;

/* Variables and functions */
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* pattern_seqs ; 

__attribute__((used)) static void
dump_pattern_seqs (void)
{
  pattern_seq pseq;
  matching_seq mseq;

  if (!dump_file)
    return;

  fprintf (dump_file, ";; Pattern sequences\n");
  for (pseq = pattern_seqs; pseq; pseq = pseq->next_pattern_seq)
    {
      fprintf (dump_file, "Pattern sequence at insn %d matches sequences at",
               INSN_UID (pseq->insn));
      for (mseq = pseq->matching_seqs; mseq; mseq = mseq->next_matching_seq)
        {
          fprintf (dump_file, " insn %d (length %d)", INSN_UID (mseq->insn),
                   mseq->matching_length);
          if (mseq->next_matching_seq)
            fprintf (dump_file, ",");
        }
      fprintf (dump_file, ".\n");
    }
  fprintf (dump_file, "\n");
}