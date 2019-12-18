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
struct stab_types {int dummy; } ;
struct stab_handle {int files; struct stab_types** file_types; struct bincl_file* bincl_list; } ;
struct bincl_file {scalar_t__ hash; struct stab_types* file_types; int /*<<< orphan*/  name; struct bincl_file* next; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xrealloc (struct stab_types**,int) ; 

__attribute__((used)) static bfd_boolean
find_excl (struct stab_handle *info, const char *name, bfd_vma hash)
{
  struct bincl_file *l;

  ++info->files;
  info->file_types = ((struct stab_types **)
		      xrealloc (info->file_types,
				(info->files
				 * sizeof *info->file_types)));

  for (l = info->bincl_list; l != NULL; l = l->next)
    if (l->hash == hash && strcmp (l->name, name) == 0)
      break;
  if (l == NULL)
    {
      warn_stab (name, _("Undefined N_EXCL"));
      info->file_types[info->files - 1] = NULL;
      return TRUE;
    }

  info->file_types[info->files - 1] = l->file_types;

  return TRUE;
}