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
 int /*<<< orphan*/  CLEAR_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_modify_mem_tables () ; 
 int /*<<< orphan*/  reg_set_bitmap ; 

__attribute__((used)) static void
reset_opr_set_tables (void)
{
  /* Maintain a bitmap of which regs have been set since beginning of
     the block.  */
  CLEAR_REG_SET (reg_set_bitmap);

  /* Also keep a record of the last instruction to modify memory.
     For now this is very trivial, we only record whether any memory
     location has been modified.  */
  clear_modify_mem_tables ();
}