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
 int /*<<< orphan*/  DF_USES_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  def_entry ; 
 int /*<<< orphan*/  df ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int see_handle_relevant_defs () ; 
 int see_handle_relevant_uses () ; 
 int /*<<< orphan*/  see_update_defs_relevancy () ; 
 int /*<<< orphan*/  see_update_leader_extra_info ; 
 int /*<<< orphan*/  see_update_uses_relevancy () ; 
 int /*<<< orphan*/  union_defs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_entry ; 
 unsigned int uses_num ; 

__attribute__((used)) static bool
see_propagate_extensions_to_uses (void)
{
  unsigned int i = 0;
  int num_relevant_uses;
  int num_relevant_defs;

  if (dump_file)
    fprintf (dump_file,
      "* Phase 1: Propagate extensions to uses.  *\n");

  /* Update the relevancy of references using the DF object.  */
  see_update_defs_relevancy ();
  see_update_uses_relevancy ();

  /* Produce the webs and update the extra_info of the root.
     In general, a web is relevant if all its definitions and uses are relevant
     and there is at least one definition that was marked as SIGN_EXTENDED_DEF
     or ZERO_EXTENDED_DEF.  */
  for (i = 0; i < uses_num; i++)
    union_defs (df, DF_USES_GET (df, i), def_entry, use_entry,
		see_update_leader_extra_info);

  /* Generate use extensions for references and insert these
     references to see_bb_splay_ar data structure.    */
  num_relevant_uses = see_handle_relevant_uses ();

  if (num_relevant_uses < 0)
    return false;

  /* Store the def extensions in their references structures and insert these
     references to see_bb_splay_ar data structure.    */
  num_relevant_defs = see_handle_relevant_defs ();

  if (num_relevant_defs < 0)
    return false;

 return num_relevant_uses > 0 || num_relevant_defs > 0;
}