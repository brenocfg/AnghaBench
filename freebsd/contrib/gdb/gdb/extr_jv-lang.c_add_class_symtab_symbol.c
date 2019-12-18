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
struct symbol {int dummy; } ;
struct blockvector {int dummy; } ;

/* Variables and functions */
 struct blockvector* BLOCKVECTOR (struct symtab*) ; 
 int /*<<< orphan*/  BLOCKVECTOR_BLOCK (struct blockvector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_DICT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_BLOCK ; 
 int /*<<< orphan*/  dict_add_symbol (int /*<<< orphan*/ ,struct symbol*) ; 
 struct symtab* get_java_class_symtab () ; 

__attribute__((used)) static void
add_class_symtab_symbol (struct symbol *sym)
{
  struct symtab *symtab = get_java_class_symtab ();
  struct blockvector *bv = BLOCKVECTOR (symtab);
  dict_add_symbol (BLOCK_DICT (BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK)), sym);
}