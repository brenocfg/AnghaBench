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
struct macro_table {int /*<<< orphan*/  definitions; } ;
struct macro_source_file {struct macro_table* table; } ;
struct macro_key {int dummy; } ;
struct macro_definition {int dummy; } ;
typedef  int /*<<< orphan*/  splay_tree_value ;
typedef  int /*<<< orphan*/  splay_tree_key ;

/* Variables and functions */
 struct macro_key* check_for_redefinition (struct macro_source_file*,int,char const*,int /*<<< orphan*/ ,int,char const**,char const*) ; 
 int /*<<< orphan*/  key_compare (struct macro_key*,char const*,struct macro_source_file*,int) ; 
 int /*<<< orphan*/  macro_function_like ; 
 struct macro_definition* new_macro_definition (struct macro_table*,int /*<<< orphan*/ ,int,char const**,char const*) ; 
 struct macro_key* new_macro_key (struct macro_table*,char const*,struct macro_source_file*,int) ; 
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
macro_define_function (struct macro_source_file *source, int line,
                       const char *name, int argc, const char **argv,
                       const char *replacement)
{
  struct macro_table *t = source->table;
  struct macro_key *k;
  struct macro_definition *d;

  k = check_for_redefinition (source, line,
                              name, macro_function_like,
                              argc, argv,
                              replacement);

  /* See comments about duplicate keys in macro_define_object.  */
  if (k && ! key_compare (k, name, source, line))
    return;

  /* We should also check here that all the argument names in ARGV are
     distinct.  */

  k = new_macro_key (t, name, source, line);
  d = new_macro_definition (t, macro_function_like, argc, argv, replacement);
  splay_tree_insert (t->definitions, (splay_tree_key) k, (splay_tree_value) d);
}