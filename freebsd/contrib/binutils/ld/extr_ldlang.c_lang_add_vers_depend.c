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
struct bfd_elf_version_tree {int /*<<< orphan*/  name; struct bfd_elf_version_tree* next; } ;
struct bfd_elf_version_deps {struct bfd_elf_version_tree* version_needed; struct bfd_elf_version_deps* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*) ; 
 struct bfd_elf_version_tree* lang_elf_version_info ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct bfd_elf_version_deps* xmalloc (int) ; 

struct bfd_elf_version_deps *
lang_add_vers_depend (struct bfd_elf_version_deps *list, const char *name)
{
  struct bfd_elf_version_deps *ret;
  struct bfd_elf_version_tree *t;

  ret = xmalloc (sizeof *ret);
  ret->next = list;

  for (t = lang_elf_version_info; t != NULL; t = t->next)
    {
      if (strcmp (t->name, name) == 0)
	{
	  ret->version_needed = t;
	  return ret;
	}
    }

  einfo (_("%X%P: unable to find version dependency `%s'\n"), name);

  return ret;
}