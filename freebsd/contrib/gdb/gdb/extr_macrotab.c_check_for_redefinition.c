#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct macro_source_file {int /*<<< orphan*/  filename; } ;
struct macro_key {int /*<<< orphan*/  start_line; TYPE_1__* start_file; } ;
struct macro_definition {int kind; int argc; int /*<<< orphan*/ * argv; int /*<<< orphan*/  replacement; } ;
typedef  TYPE_2__* splay_tree_node ;
typedef  enum macro_kind { ____Placeholder_macro_kind } macro_kind ;
struct TYPE_5__ {scalar_t__ value; scalar_t__ key; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* find_definition (char const*,struct macro_source_file*,int) ; 
 int macro_function_like ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static struct macro_key *
check_for_redefinition (struct macro_source_file *source, int line,
                        const char *name, enum macro_kind kind,
                        int argc, const char **argv,
                        const char *replacement)
{
  splay_tree_node n = find_definition (name, source, line);

  if (n)
    {
      struct macro_key *found_key = (struct macro_key *) n->key;
      struct macro_definition *found_def
        = (struct macro_definition *) n->value;
      int same = 1;

      /* Is this definition the same as the existing one?
         According to the standard, this comparison needs to be done
         on lists of tokens, not byte-by-byte, as we do here.  But
         that's too hard for us at the moment, and comparing
         byte-by-byte will only yield false negatives (i.e., extra
         warning messages), not false positives (i.e., unnoticed
         definition changes).  */
      if (kind != found_def->kind)
        same = 0;
      else if (strcmp (replacement, found_def->replacement))
        same = 0;
      else if (kind == macro_function_like)
        {
          if (argc != found_def->argc)
            same = 0;
          else
            {
              int i;

              for (i = 0; i < argc; i++)
                if (strcmp (argv[i], found_def->argv[i]))
                  same = 0;
            }
        }

      if (! same)
        {
	  complaint (&symfile_complaints,
		     "macro `%s' redefined at %s:%d; original definition at %s:%d",
		     name, source->filename, line,
		     found_key->start_file->filename, found_key->start_line);
        }

      return found_key;
    }
  else
    return 0;
}