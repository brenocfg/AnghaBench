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
struct blockvector {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 struct blockvector* BLOCKVECTOR (struct symtab*) ; 
 struct block* BLOCKVECTOR_BLOCK (struct blockvector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_DICT (struct block*) ; 
 int /*<<< orphan*/  GLOBAL_BLOCK ; 
 int /*<<< orphan*/  dict_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_class_block (struct symtab *symtab)
{
  struct blockvector *bv = BLOCKVECTOR (symtab);
  struct block *bl = BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK);

  dict_free (BLOCK_DICT (bl));
}