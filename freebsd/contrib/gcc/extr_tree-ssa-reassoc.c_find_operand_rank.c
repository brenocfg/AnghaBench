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
typedef  int /*<<< orphan*/  tree ;
struct operand_entry {int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/ * operand_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  NO_INSERT ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct operand_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  operand_rank ; 

__attribute__((used)) static operand_entry_t
find_operand_rank (tree e)
{
  void **slot;
  struct operand_entry vrd;

  vrd.op = e;
  slot = htab_find_slot (operand_rank, &vrd, NO_INSERT);
  if (!slot)
    return NULL;
  return ((operand_entry_t) *slot);
}