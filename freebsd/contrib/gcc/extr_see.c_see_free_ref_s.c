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
struct see_ref_s {scalar_t__ use_se_hash; scalar_t__ merged_def_se_hash; scalar_t__ unmerged_def_se_hash; } ;
typedef  scalar_t__ splay_tree_value ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct see_ref_s*) ; 
 int /*<<< orphan*/  htab_delete (scalar_t__) ; 

__attribute__((used)) static void
see_free_ref_s (splay_tree_value value)
{
  struct see_ref_s *ref_s = (struct see_ref_s *)value;

  if (ref_s->unmerged_def_se_hash)
    htab_delete (ref_s->unmerged_def_se_hash);
  if (ref_s->merged_def_se_hash)
    htab_delete (ref_s->merged_def_se_hash);
  if (ref_s->use_se_hash)
    htab_delete (ref_s->use_se_hash);
  free (ref_s);
}