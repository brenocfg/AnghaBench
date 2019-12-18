#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct macro_table {int /*<<< orphan*/  definitions; } ;
struct macro_source_file {struct macro_table* table; } ;
struct macro_key {char const* name; int start_line; int /*<<< orphan*/  end_line; int /*<<< orphan*/ * end_file; struct macro_source_file* start_file; } ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_5__ {scalar_t__ key; } ;

/* Variables and functions */
 scalar_t__ compare_locations (struct macro_source_file*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* splay_tree_predecessor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static splay_tree_node
find_definition (const char *name,
                 struct macro_source_file *file,
                 int line)
{
  struct macro_table *t = file->table;
  splay_tree_node n;

  /* Construct a macro_key object, just for the query.  */
  struct macro_key query;

  query.name = name;
  query.start_file = file;
  query.start_line = line;
  query.end_file = NULL;

  n = splay_tree_lookup (t->definitions, (splay_tree_key) &query);
  if (! n)
    {
      /* It's okay for us to do two queries like this: the real work
         of the searching is done when we splay, and splaying the tree
         a second time at the same key is a constant time operation.
         If this still bugs you, you could always just extend the
         splay tree library with a predecessor-or-equal operation, and
         use that.  */
      splay_tree_node pred = splay_tree_predecessor (t->definitions,
                                                     (splay_tree_key) &query);
     
      if (pred)
        {
          /* Make sure this predecessor actually has the right name.
             We just want to search within a given name's definitions.  */
          struct macro_key *found = (struct macro_key *) pred->key;

          if (strcmp (found->name, name) == 0)
            n = pred;
        }
    }

  if (n)
    {
      struct macro_key *found = (struct macro_key *) n->key;

      /* Okay, so this definition has the right name, and its scope
         begins before the given source location.  But does its scope
         end after the given source location?  */
      if (compare_locations (file, line, found->end_file, found->end_line) < 0)
        return n;
      else
        return 0;
    }
  else
    return 0;
}