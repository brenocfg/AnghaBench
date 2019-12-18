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
struct value {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int ada_lookup_symbol_list (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symbol***,struct block***) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ *) ; 
 struct value* value_of_variable (struct symbol*,struct block*) ; 

__attribute__((used)) static struct value *
get_var_value (char *name, char *err_msg)
{
  struct symbol **syms;
  struct block **blocks;
  int nsyms;

  nsyms =
    ada_lookup_symbol_list (name, get_selected_block (NULL), VAR_DOMAIN,
			    &syms, &blocks);

  if (nsyms != 1)
    {
      if (err_msg == NULL)
	return 0;
      else
	error ("%s", err_msg);
    }

  return value_of_variable (syms[0], blocks[0]);
}