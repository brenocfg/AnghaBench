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
struct objfile {int /*<<< orphan*/ * cp_namespace_symtab; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKVECTOR (int /*<<< orphan*/ *) ; 
 struct block* BLOCKVECTOR_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRST_LOCAL_BLOCK ; 
 int /*<<< orphan*/  initialize_namespace_symtab (struct objfile*) ; 

__attribute__((used)) static struct block *
get_possible_namespace_block (struct objfile *objfile)
{
  if (objfile->cp_namespace_symtab == NULL)
    initialize_namespace_symtab (objfile);

  return BLOCKVECTOR_BLOCK (BLOCKVECTOR (objfile->cp_namespace_symtab),
			    FIRST_LOCAL_BLOCK);
}