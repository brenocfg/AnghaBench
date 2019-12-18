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
struct TYPE_2__ {struct bfd_elf_version_expr* remaining; scalar_t__ htab; struct bfd_elf_version_expr* list; } ;
struct bfd_elf_version_tree {char* name; struct bfd_elf_version_tree* next; scalar_t__ vernum; struct bfd_elf_version_deps* deps; TYPE_1__ globals; TYPE_1__ locals; } ;
struct bfd_elf_version_expr {char* symbol; scalar_t__ mask; char* pattern; struct bfd_elf_version_expr* next; } ;
struct bfd_elf_version_deps {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (struct bfd_elf_version_tree*) ; 
 struct bfd_elf_version_expr* htab_find (scalar_t__,struct bfd_elf_version_expr*) ; 
 struct bfd_elf_version_tree* lang_elf_version_info ; 
 int /*<<< orphan*/  lang_finalize_version_expr_head (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ version_index ; 

void
lang_register_vers_node (const char *name,
			 struct bfd_elf_version_tree *version,
			 struct bfd_elf_version_deps *deps)
{
  struct bfd_elf_version_tree *t, **pp;
  struct bfd_elf_version_expr *e1;

  if (name == NULL)
    name = "";

  if ((name[0] == '\0' && lang_elf_version_info != NULL)
      || (lang_elf_version_info && lang_elf_version_info->name[0] == '\0'))
    {
      einfo (_("%X%P: anonymous version tag cannot be combined"
	       " with other version tags\n"));
      free (version);
      return;
    }

  /* Make sure this node has a unique name.  */
  for (t = lang_elf_version_info; t != NULL; t = t->next)
    if (strcmp (t->name, name) == 0)
      einfo (_("%X%P: duplicate version tag `%s'\n"), name);

  lang_finalize_version_expr_head (&version->globals);
  lang_finalize_version_expr_head (&version->locals);

  /* Check the global and local match names, and make sure there
     aren't any duplicates.  */

  for (e1 = version->globals.list; e1 != NULL; e1 = e1->next)
    {
      for (t = lang_elf_version_info; t != NULL; t = t->next)
	{
	  struct bfd_elf_version_expr *e2;

	  if (t->locals.htab && e1->symbol)
	    {
	      e2 = htab_find (t->locals.htab, e1);
	      while (e2 && strcmp (e1->symbol, e2->symbol) == 0)
		{
		  if (e1->mask == e2->mask)
		    einfo (_("%X%P: duplicate expression `%s'"
			     " in version information\n"), e1->symbol);
		  e2 = e2->next;
		}
	    }
	  else if (!e1->symbol)
	    for (e2 = t->locals.remaining; e2 != NULL; e2 = e2->next)
	      if (strcmp (e1->pattern, e2->pattern) == 0
		  && e1->mask == e2->mask)
		einfo (_("%X%P: duplicate expression `%s'"
			 " in version information\n"), e1->pattern);
	}
    }

  for (e1 = version->locals.list; e1 != NULL; e1 = e1->next)
    {
      for (t = lang_elf_version_info; t != NULL; t = t->next)
	{
	  struct bfd_elf_version_expr *e2;

	  if (t->globals.htab && e1->symbol)
	    {
	      e2 = htab_find (t->globals.htab, e1);
	      while (e2 && strcmp (e1->symbol, e2->symbol) == 0)
		{
		  if (e1->mask == e2->mask)
		    einfo (_("%X%P: duplicate expression `%s'"
			     " in version information\n"),
			   e1->symbol);
		  e2 = e2->next;
		}
	    }
	  else if (!e1->symbol)
	    for (e2 = t->globals.remaining; e2 != NULL; e2 = e2->next)
	      if (strcmp (e1->pattern, e2->pattern) == 0
		  && e1->mask == e2->mask)
		einfo (_("%X%P: duplicate expression `%s'"
			 " in version information\n"), e1->pattern);
	}
    }

  version->deps = deps;
  version->name = name;
  if (name[0] != '\0')
    {
      ++version_index;
      version->vernum = version_index;
    }
  else
    version->vernum = 0;

  for (pp = &lang_elf_version_info; *pp != NULL; pp = &(*pp)->next)
    ;
  *pp = version;
}