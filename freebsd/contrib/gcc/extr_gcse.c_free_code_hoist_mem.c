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
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  antloc ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hoist_exprs ; 
 int /*<<< orphan*/  hoist_vbein ; 
 int /*<<< orphan*/  hoist_vbeout ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transp ; 
 int /*<<< orphan*/  transpout ; 

__attribute__((used)) static void
free_code_hoist_mem (void)
{
  sbitmap_vector_free (antloc);
  sbitmap_vector_free (transp);
  sbitmap_vector_free (comp);

  sbitmap_vector_free (hoist_vbein);
  sbitmap_vector_free (hoist_vbeout);
  sbitmap_vector_free (hoist_exprs);
  sbitmap_vector_free (transpout);

  free_dominance_info (CDI_DOMINATORS);
}