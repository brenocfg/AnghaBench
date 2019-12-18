#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vla_hwint_t ;
typedef  TYPE_2__* automaton_t ;
typedef  TYPE_3__* ainsn_t ;
struct TYPE_10__ {int insns_num; } ;
struct TYPE_9__ {int /*<<< orphan*/  insn_equiv_class_num; TYPE_1__* insn_reserv_decl; struct TYPE_9__* next_ainsn; } ;
struct TYPE_8__ {int /*<<< orphan*/  insn_equiv_classes_num; TYPE_3__* ainsn_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  insn_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_quick_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* description ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  output_range_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_translate_vect_name (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  output_vect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_el_t ; 

__attribute__((used)) static void
output_translate_vect (automaton_t automaton)
{
  ainsn_t ainsn;
  int insn_value;
  vla_hwint_t translate_vect;

  translate_vect = VEC_alloc (vect_el_t,heap, description->insns_num);

  for (insn_value = 0; insn_value < description->insns_num; insn_value++)
    /* Undefined value */
    VEC_quick_push (vect_el_t, translate_vect,
		    automaton->insn_equiv_classes_num);

  for (ainsn = automaton->ainsn_list; ainsn != NULL; ainsn = ainsn->next_ainsn)
    VEC_replace (vect_el_t, translate_vect,
		 ainsn->insn_reserv_decl->insn_num,
		 ainsn->insn_equiv_class_num);

  fprintf (output_file,
           "/* Vector translating external insn codes to internal ones.*/\n");
  fprintf (output_file, "static const ");
  output_range_type (output_file, 0, automaton->insn_equiv_classes_num);
  fprintf (output_file, " ");
  output_translate_vect_name (output_file, automaton);
  fprintf (output_file, "[] ATTRIBUTE_UNUSED = {\n");
  output_vect (translate_vect);
  fprintf (output_file, "};\n\n");
  VEC_free (vect_el_t,heap, translate_vect);
}