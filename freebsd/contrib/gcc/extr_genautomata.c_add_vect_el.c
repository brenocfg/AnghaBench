#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vla_hwint_t ;
typedef  TYPE_1__* ainsn_t ;
struct TYPE_4__ {int insn_equiv_class_num; } ;

/* Variables and functions */
 int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VEC_safe_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  undefined_vect_el_value ; 
 int /*<<< orphan*/  vect_el_t ; 

__attribute__((used)) static void
add_vect_el (vla_hwint_t *vect, ainsn_t ainsn, int el_value)
{
  int equiv_class_num;
  int vect_index;

  gcc_assert (ainsn);
  equiv_class_num = ainsn->insn_equiv_class_num;
  for (vect_index = VEC_length (vect_el_t, *vect);
       vect_index <= equiv_class_num;
       vect_index++)
    VEC_safe_push (vect_el_t,heap, *vect, undefined_vect_el_value);
  VEC_replace (vect_el_t, *vect, equiv_class_num, el_value);
}