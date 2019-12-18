#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {char* (* strip_name_encoding ) (char const*) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ASSEMBLER_NAME_SET_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_WEAK (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VISIBILITY_HIDDEN ; 
 char* concat (char*,int /*<<< orphan*/ ,char const*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int name_needs_quotes (char const*) ; 
 int /*<<< orphan*/  no_dead_strip (int /*<<< orphan*/ *,char*) ; 
 char* stub1 (char const*) ; 
 TYPE_1__ targetm ; 
 int /*<<< orphan*/  user_label_prefix ; 

void
darwin_emit_unwind_label (FILE *file, tree decl, int for_eh, int empty)
{
  const char *base;
  char *lab;
  bool need_quotes;

  if (DECL_ASSEMBLER_NAME_SET_P (decl))
    base = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
  else
    base = IDENTIFIER_POINTER (DECL_NAME (decl));

  base = targetm.strip_name_encoding (base);
  need_quotes = name_needs_quotes (base);

  if (! for_eh)
    return;

  lab = concat (need_quotes ? "\"" : "", user_label_prefix, base, ".eh",
		need_quotes ? "\"" : "", NULL);

  if (TREE_PUBLIC (decl))
    fprintf (file, "\t%s %s\n",
	     (DECL_VISIBILITY (decl) != VISIBILITY_HIDDEN
	      ? ".globl"
	      : ".private_extern"),
	     lab);

  if (DECL_WEAK (decl))
    fprintf (file, "\t.weak_definition %s\n", lab);

  if (empty)
    {
      fprintf (file, "%s = 0\n", lab);

      /* Mark the absolute .eh and .eh1 style labels as needed to
	 ensure that we don't dead code strip them and keep such
	 labels from another instantiation point until we can fix this
	 properly with group comdat support.  */
      no_dead_strip (file, lab);
    }
  else
    fprintf (file, "%s:\n", lab);

  free (lab);
}