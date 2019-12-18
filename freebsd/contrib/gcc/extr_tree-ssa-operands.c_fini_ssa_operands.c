#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ssa_operand_memory_d {struct ssa_operand_memory_d* next; } ;
struct TYPE_2__ {int clobbered_vars; int static_write_clobbers_avoided; int static_read_clobbers_avoided; int unescapable_clobbers_avoided; int readonly_clobbers; int static_readonly_clobbers_avoided; } ;

/* Variables and functions */
 int TDF_STATS ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_defs ; 
 int /*<<< orphan*/  build_uses ; 
 int /*<<< orphan*/  build_v_may_defs ; 
 int /*<<< orphan*/  build_v_must_defs ; 
 int /*<<< orphan*/  build_vuses ; 
 TYPE_1__ clobber_stats ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/ * free_defs ; 
 int /*<<< orphan*/ * free_maydefs ; 
 int /*<<< orphan*/ * free_mustdefs ; 
 int /*<<< orphan*/ * free_uses ; 
 int /*<<< orphan*/ * free_vuses ; 
 int /*<<< orphan*/  ggc_free (struct ssa_operand_memory_d*) ; 
 int /*<<< orphan*/  heap ; 
 struct ssa_operand_memory_d* operand_memory ; 
 int ops_active ; 
 int /*<<< orphan*/  tree ; 

void
fini_ssa_operands (void)
{
  struct ssa_operand_memory_d *ptr;
  VEC_free (tree, heap, build_defs);
  VEC_free (tree, heap, build_uses);
  VEC_free (tree, heap, build_v_must_defs);
  VEC_free (tree, heap, build_v_may_defs);
  VEC_free (tree, heap, build_vuses);
  free_defs = NULL;
  free_uses = NULL;
  free_vuses = NULL;
  free_maydefs = NULL;
  free_mustdefs = NULL;
  while ((ptr = operand_memory) != NULL)
    {
      operand_memory = operand_memory->next;
      ggc_free (ptr);
    }

  ops_active = false;
  
  if (dump_file && (dump_flags & TDF_STATS))
    {
      fprintf (dump_file, "Original clobbered vars:%d\n",
	       clobber_stats.clobbered_vars);
      fprintf (dump_file, "Static write clobbers avoided:%d\n",
	       clobber_stats.static_write_clobbers_avoided);
      fprintf (dump_file, "Static read clobbers avoided:%d\n",
	       clobber_stats.static_read_clobbers_avoided);
      fprintf (dump_file, "Unescapable clobbers avoided:%d\n",
	       clobber_stats.unescapable_clobbers_avoided);
      fprintf (dump_file, "Original read-only clobbers:%d\n",
	       clobber_stats.readonly_clobbers);
      fprintf (dump_file, "Static read-only clobbers avoided:%d\n",
	       clobber_stats.static_readonly_clobbers_avoided);
    }
}