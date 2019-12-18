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
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decide_instantiations () ; 
 scalar_t__ find_candidates_for_sra () ; 
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  needs_copy_in ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scalarize_function () ; 
 int /*<<< orphan*/  scan_function () ; 
 int /*<<< orphan*/  sra_candidates ; 
 int /*<<< orphan*/  sra_elt_eq ; 
 int /*<<< orphan*/  sra_elt_hash ; 
 int /*<<< orphan*/  sra_init_cache () ; 
 int /*<<< orphan*/ * sra_map ; 
 int /*<<< orphan*/  sra_obstack ; 
 int /*<<< orphan*/  sra_type_decomp_cache ; 
 int /*<<< orphan*/  sra_type_inst_cache ; 
 unsigned int todoflags ; 

__attribute__((used)) static unsigned int
tree_sra (void)
{
  /* Initialize local variables.  */
  todoflags = 0;
  gcc_obstack_init (&sra_obstack);
  sra_candidates = BITMAP_ALLOC (NULL);
  needs_copy_in = BITMAP_ALLOC (NULL);
  sra_init_cache ();
  sra_map = htab_create (101, sra_elt_hash, sra_elt_eq, NULL);

  /* Scan.  If we find anything, instantiate and scalarize.  */
  if (find_candidates_for_sra ())
    {
      scan_function ();
      decide_instantiations ();
      scalarize_function ();
    }

  /* Free allocated memory.  */
  htab_delete (sra_map);
  sra_map = NULL;
  BITMAP_FREE (sra_candidates);
  BITMAP_FREE (needs_copy_in);
  BITMAP_FREE (sra_type_decomp_cache);
  BITMAP_FREE (sra_type_inst_cache);
  obstack_free (&sra_obstack, NULL);
  return todoflags;
}