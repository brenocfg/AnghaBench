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

/* Variables and functions */
 int CLEANUP_CROSSJUMP ; 
 int CLEANUP_EXPENSIVE ; 
 int CLEANUP_UPDATE_LIFE ; 
 int /*<<< orphan*/  HASH_INIT ; 
 int PROP_DEATH_NOTES ; 
 int PROP_KILL_DEAD_CODE ; 
 int PROP_SCAN_DEAD_CODE ; 
 int /*<<< orphan*/  abstract_best_seq () ; 
 int /*<<< orphan*/  cleanup_cfg (int) ; 
 int /*<<< orphan*/  collect_pattern_seqs () ; 
 int /*<<< orphan*/  compute_init_costs () ; 
 int /*<<< orphan*/  count_or_remove_death_notes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dump_best_pattern_seq (int) ; 
 int /*<<< orphan*/  dump_pattern_seqs () ; 
 int /*<<< orphan*/  fill_hash_bucket () ; 
 scalar_t__ flag_crossjumping ; 
 int /*<<< orphan*/  hash_buckets ; 
 int /*<<< orphan*/  htab_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_del_bucket ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_eq_bucket ; 
 int /*<<< orphan*/  htab_hash_bucket ; 
 int /*<<< orphan*/  life_analysis (int) ; 
 int /*<<< orphan*/  pattern_seqs ; 
 int /*<<< orphan*/  recompute_gain () ; 
 int /*<<< orphan*/  update_pattern_seqs () ; 

__attribute__((used)) static void
rtl_seqabstr (void)
{
  int iter;

  /* Create a hash list for COLLECT_PATTERN_SEQS.  */
  hash_buckets = htab_create (HASH_INIT, htab_hash_bucket , htab_eq_bucket ,
                              htab_del_bucket);
  fill_hash_bucket ();

  /* Compute the common cost of abstraction.  */
  compute_init_costs ();

  /* Build an initial set of pattern sequences from the current function.  */
  collect_pattern_seqs ();
  dump_pattern_seqs ();

  /* Iterate until there are no sequences to abstract.  */
  for (iter = 1;; iter++)
    {
      /* Recompute gain for sequences if necessary and select sequence with
         biggest gain.  */
      recompute_gain ();
      if (!pattern_seqs)
        break;
      dump_best_pattern_seq (iter);
      /* Update the cached info of the other sequences and force gain
         recomputation where needed.  */
      update_pattern_seqs ();
      /* Turn best sequences into pseudo-functions and -calls.  */
      abstract_best_seq ();
    }

  /* Cleanup hash tables.  */
  htab_delete (hash_buckets);

  if (iter > 1)
    {
      /* Update notes.  */
      count_or_remove_death_notes (NULL, 1);

      life_analysis (PROP_DEATH_NOTES | PROP_SCAN_DEAD_CODE
		     | PROP_KILL_DEAD_CODE);

      /* Extra cleanup.  */
      cleanup_cfg (CLEANUP_EXPENSIVE |
                   CLEANUP_UPDATE_LIFE |
                   (flag_crossjumping ? CLEANUP_CROSSJUMP : 0));
    }
}