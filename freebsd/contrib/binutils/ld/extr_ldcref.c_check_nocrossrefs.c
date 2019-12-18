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
 int /*<<< orphan*/  check_local_sym_xref ; 
 int /*<<< orphan*/  check_nocrossref ; 
 int /*<<< orphan*/  cref_hash_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cref_initialized ; 
 int /*<<< orphan*/  cref_table ; 
 int /*<<< orphan*/  lang_for_each_file (int /*<<< orphan*/ ) ; 

void
check_nocrossrefs (void)
{
  if (! cref_initialized)
    return;

  cref_hash_traverse (&cref_table, check_nocrossref, NULL);

  lang_for_each_file (check_local_sym_xref);
}