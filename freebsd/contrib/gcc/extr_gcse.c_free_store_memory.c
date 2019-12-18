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
 int /*<<< orphan*/ * ae_gen ; 
 int /*<<< orphan*/ * ae_kill ; 
 int /*<<< orphan*/  free_ldst_mems () ; 
 int /*<<< orphan*/ * pre_delete_map ; 
 int /*<<< orphan*/ * pre_insert_map ; 
 int /*<<< orphan*/ * reg_set_in_block ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * st_antloc ; 
 int /*<<< orphan*/ * transp ; 

__attribute__((used)) static void
free_store_memory (void)
{
  free_ldst_mems ();

  if (ae_gen)
    sbitmap_vector_free (ae_gen);
  if (ae_kill)
    sbitmap_vector_free (ae_kill);
  if (transp)
    sbitmap_vector_free (transp);
  if (st_antloc)
    sbitmap_vector_free (st_antloc);
  if (pre_insert_map)
    sbitmap_vector_free (pre_insert_map);
  if (pre_delete_map)
    sbitmap_vector_free (pre_delete_map);
  if (reg_set_in_block)
    sbitmap_vector_free (reg_set_in_block);

  ae_gen = ae_kill = transp = st_antloc = NULL;
  pre_insert_map = pre_delete_map = reg_set_in_block = NULL;
}