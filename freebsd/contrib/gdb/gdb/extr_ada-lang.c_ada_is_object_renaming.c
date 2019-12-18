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
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 char* ada_renaming_type (int /*<<< orphan*/ ) ; 

int
ada_is_object_renaming (struct symbol *sym)
{
  const char *renaming_type = ada_renaming_type (SYMBOL_TYPE (sym));
  return renaming_type != NULL
    && (renaming_type[2] == '\0' || renaming_type[2] == '_');
}