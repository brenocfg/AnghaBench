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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct symbol**) ; 
 int /*<<< orphan*/  make_symbol_overload_list_using (char const*,char const*) ; 
 struct symbol** sym_return_val ; 
 scalar_t__ sym_return_val_index ; 
 int sym_return_val_size ; 
 int /*<<< orphan*/  xfree ; 
 struct symbol** xmalloc (int) ; 

struct symbol **
make_symbol_overload_list (const char *func_name,
			   const char *namespace)
{
  struct cleanup *old_cleanups;

  sym_return_val_size = 100;
  sym_return_val_index = 0;
  sym_return_val = xmalloc ((sym_return_val_size + 1) *
			    sizeof (struct symbol *));
  sym_return_val[0] = NULL;

  old_cleanups = make_cleanup (xfree, sym_return_val);

  make_symbol_overload_list_using (func_name, namespace);

  discard_cleanups (old_cleanups);

  return sym_return_val;
}