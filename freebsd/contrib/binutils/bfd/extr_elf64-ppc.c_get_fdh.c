#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ppc_link_hash_table {int /*<<< orphan*/  elf; } ;
struct TYPE_4__ {char* string; } ;
struct TYPE_5__ {TYPE_1__ root; } ;
struct TYPE_6__ {TYPE_2__ root; } ;
struct ppc_link_hash_entry {int is_func_descriptor; int is_func; struct ppc_link_hash_entry* oh; TYPE_3__ elf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ elf_link_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ppc_link_hash_entry *
get_fdh (struct ppc_link_hash_entry *fh, struct ppc_link_hash_table *htab)
{
  struct ppc_link_hash_entry *fdh = fh->oh;

  if (fdh == NULL)
    {
      const char *fd_name = fh->elf.root.root.string + 1;

      fdh = (struct ppc_link_hash_entry *)
	elf_link_hash_lookup (&htab->elf, fd_name, FALSE, FALSE, FALSE);
      if (fdh != NULL)
	{
	  fdh->is_func_descriptor = 1;
	  fdh->oh = fh;
	  fh->is_func = 1;
	  fh->oh = fdh;
	}
    }

  return fdh;
}