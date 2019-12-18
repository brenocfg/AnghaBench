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
 struct macro_key* check_for_redefinition (struct macro_source_file*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  key_compare (struct macro_key*,char const*,struct macro_source_file*,int) ; 
 int /*<<< orphan*/  macro_object_like ; 
 struct macro_definition* new_macro_definition (struct macro_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 struct macro_key* new_macro_key (struct macro_table*,char const*,struct macro_source_file*,int) ; 
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
macro_define_object (struct macro_source_file *source, int line,
                     const char *name, const char *replacement)
{
  struct macro_table *t = source->table;
  struct macro_key *k;
  struct macro_definition *d;

  k = check_for_redefinition (source, line, 
                              name, macro_object_like,
                              0, 0,
                              replacement);

  /* If we're redefining a symbol, and the existing key would be
     identical to our new key, then the splay_tree_insert function
     will try to delete the old definition.  When the definition is
     living on an obstack, this isn't a happy thing.

     Since this only happens in the presence of questionable debug
     info, we just ignore all definitions after the first.  The only
     case I know of where this arises is in GCC's output for
     predefined macros, and all the definitions are the same in that
     case.  */
  if (k && ! key_compare (k, name, source, line))
    return;

  k = new_macro_key (t, name, source, line);
  d = new_macro_definition (t, macro_object_like, 0, 0, replacement);
  splay_tree_insert (t->definitions, (splay_tree_key) k, (splay_tree_value) d);
}