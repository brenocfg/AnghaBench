#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct elt_list {TYPE_2__* elt; struct elt_list* next; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {int /*<<< orphan*/  val_rtx; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; TYPE_1__ u; struct elt_list* addr_list; } ;
typedef  TYPE_2__ cselib_val ;

/* Variables and functions */
 int BLKmode ; 
 scalar_t__ FLOAT_MODE_P (int) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSERT ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mem_for_addr (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cselib_hash_table ; 
 TYPE_2__* cselib_lookup (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cselib_record_memory ; 
 scalar_t__ flag_float_store ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* new_cselib_val (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_unknown_value ; 
 int /*<<< orphan*/  wrap_constant (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cselib_val *
cselib_lookup_mem (rtx x, int create)
{
  enum machine_mode mode = GET_MODE (x);
  void **slot;
  cselib_val *addr;
  cselib_val *mem_elt;
  struct elt_list *l;

  if (MEM_VOLATILE_P (x) || mode == BLKmode
      || !cselib_record_memory
      || (FLOAT_MODE_P (mode) && flag_float_store))
    return 0;

  /* Look up the value for the address.  */
  addr = cselib_lookup (XEXP (x, 0), mode, create);
  if (! addr)
    return 0;

  /* Find a value that describes a value of our mode at that address.  */
  for (l = addr->addr_list; l; l = l->next)
    if (GET_MODE (l->elt->u.val_rtx) == mode)
      return l->elt;

  if (! create)
    return 0;

  mem_elt = new_cselib_val (++next_unknown_value, mode);
  add_mem_for_addr (addr, mem_elt, x);
  slot = htab_find_slot_with_hash (cselib_hash_table, wrap_constant (mode, x),
				   mem_elt->value, INSERT);
  *slot = mem_elt;
  return mem_elt;
}