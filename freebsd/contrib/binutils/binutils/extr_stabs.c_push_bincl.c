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
struct stab_handle {int files; struct stab_types** file_types; struct bincl_file* bincl_stack; struct bincl_file* bincl_list; } ;
struct bincl_file {char const* name; int file; int /*<<< orphan*/ * file_types; int /*<<< orphan*/  hash; struct bincl_file* next_stack; struct bincl_file* next; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (struct stab_types**,int) ; 

__attribute__((used)) static void
push_bincl (struct stab_handle *info, const char *name, bfd_vma hash)
{
  struct bincl_file *n;

  n = (struct bincl_file *) xmalloc (sizeof *n);
  n->next = info->bincl_list;
  n->next_stack = info->bincl_stack;
  n->name = name;
  n->hash = hash;
  n->file = info->files;
  n->file_types = NULL;
  info->bincl_list = n;
  info->bincl_stack = n;

  ++info->files;
  info->file_types = ((struct stab_types **)
		      xrealloc (info->file_types,
				(info->files
				 * sizeof *info->file_types)));
  info->file_types[n->file] = NULL;
}