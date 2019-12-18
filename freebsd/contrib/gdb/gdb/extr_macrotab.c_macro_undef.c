#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct macro_source_file {int /*<<< orphan*/  filename; } ;
struct macro_key {int end_line; struct macro_source_file* end_file; } ;
typedef  TYPE_1__* splay_tree_node ;
struct TYPE_3__ {scalar_t__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int,...) ; 
 TYPE_1__* find_definition (char const*,struct macro_source_file*,int) ; 
 int /*<<< orphan*/  symfile_complaints ; 

void
macro_undef (struct macro_source_file *source, int line,
             const char *name)
{
  splay_tree_node n = find_definition (name, source, line);

  if (n)
    {
      /* This function is the only place a macro's end-of-scope
         location gets set to anything other than "end of the
         compilation unit" (i.e., end_file is zero).  So if this macro
         already has its end-of-scope set, then we're probably seeing
         a second #undefinition for the same #definition.  */
      struct macro_key *key = (struct macro_key *) n->key;

      if (key->end_file)
        {
	  complaint (&symfile_complaints,
		     "macro '%s' is #undefined twice, at %s:%d and %s:%d", name,
		     source->filename, line, key->end_file->filename,
		     key->end_line);
        }

      /* Whatever the case, wipe out the old ending point, and 
         make this the ending point.  */
      key->end_file = source;
      key->end_line = line;
    }
  else
    {
      /* According to the ISO C standard, an #undef for a symbol that
         has no macro definition in scope is ignored.  So we should
         ignore it too.  */
#if 0
      complaint (&symfile_complaints,
		 "no definition for macro `%s' in scope to #undef at %s:%d",
		 name, source->filename, line);
#endif
    }
}