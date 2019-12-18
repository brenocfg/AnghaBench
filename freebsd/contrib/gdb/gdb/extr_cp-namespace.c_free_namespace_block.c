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
struct symtab {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKVECTOR (struct symtab*) ; 
 struct block* BLOCKVECTOR_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_DICT (struct block*) ; 
 int /*<<< orphan*/  FIRST_LOCAL_BLOCK ; 
 int /*<<< orphan*/  dict_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_namespace_block (struct symtab *symtab)
{
  struct block *possible_namespace_block;

  possible_namespace_block = BLOCKVECTOR_BLOCK (BLOCKVECTOR (symtab),
						FIRST_LOCAL_BLOCK);
  gdb_assert (possible_namespace_block != NULL);
  dict_free (BLOCK_DICT (possible_namespace_block));
}