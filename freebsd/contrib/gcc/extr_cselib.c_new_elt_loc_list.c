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
struct elt_loc_list {int /*<<< orphan*/  in_libcall; int /*<<< orphan*/  setting_insn; int /*<<< orphan*/  loc; struct elt_loc_list* next; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  cselib_current_insn ; 
 int /*<<< orphan*/  cselib_current_insn_in_libcall ; 
 int /*<<< orphan*/  elt_loc_list_pool ; 
 struct elt_loc_list* pool_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct elt_loc_list *
new_elt_loc_list (struct elt_loc_list *next, rtx loc)
{
  struct elt_loc_list *el;
  el = pool_alloc (elt_loc_list_pool);
  el->next = next;
  el->loc = loc;
  el->setting_insn = cselib_current_insn;
  el->in_libcall = cselib_current_insn_in_libcall;
  return el;
}