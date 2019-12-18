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
typedef  scalar_t__ decl_t ;

/* Variables and functions */
 void** htab_find_slot (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  insn_decl_table ; 

__attribute__((used)) static decl_t
insert_insn_decl (decl_t insn_decl)
{
  void **entry_ptr;

  entry_ptr = htab_find_slot (insn_decl_table, insn_decl, 1);
  if (*entry_ptr == NULL)
    *entry_ptr = (void *) insn_decl;
  return (decl_t) *entry_ptr;
}