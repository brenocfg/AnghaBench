#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ppc_link_hash_table {int /*<<< orphan*/  elf; } ;
struct TYPE_3__ {char* string; } ;
struct TYPE_4__ {TYPE_1__ root; } ;
struct elf_link_hash_entry {TYPE_2__ root; } ;
struct ppc_link_hash_entry {struct elf_link_hash_entry elf; struct ppc_link_hash_entry* oh; scalar_t__ is_func_descriptor; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_hide_symbol (struct bfd_link_info*,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_link_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
ppc64_elf_hide_symbol (struct bfd_link_info *info,
		       struct elf_link_hash_entry *h,
		       bfd_boolean force_local)
{
  struct ppc_link_hash_entry *eh;
  _bfd_elf_link_hash_hide_symbol (info, h, force_local);

  eh = (struct ppc_link_hash_entry *) h;
  if (eh->is_func_descriptor)
    {
      struct ppc_link_hash_entry *fh = eh->oh;

      if (fh == NULL)
	{
	  const char *p, *q;
	  struct ppc_link_hash_table *htab;
	  char save;

	  /* We aren't supposed to use alloca in BFD because on
	     systems which do not have alloca the version in libiberty
	     calls xmalloc, which might cause the program to crash
	     when it runs out of memory.  This function doesn't have a
	     return status, so there's no way to gracefully return an
	     error.  So cheat.  We know that string[-1] can be safely
	     accessed;  It's either a string in an ELF string table,
	     or allocated in an objalloc structure.  */

	  p = eh->elf.root.root.string - 1;
	  save = *p;
	  *(char *) p = '.';
	  htab = ppc_hash_table (info);
	  fh = (struct ppc_link_hash_entry *)
	    elf_link_hash_lookup (&htab->elf, p, FALSE, FALSE, FALSE);
	  *(char *) p = save;

	  /* Unfortunately, if it so happens that the string we were
	     looking for was allocated immediately before this string,
	     then we overwrote the string terminator.  That's the only
	     reason the lookup should fail.  */
	  if (fh == NULL)
	    {
	      q = eh->elf.root.root.string + strlen (eh->elf.root.root.string);
	      while (q >= eh->elf.root.root.string && *q == *p)
		--q, --p;
	      if (q < eh->elf.root.root.string && *p == '.')
		fh = (struct ppc_link_hash_entry *)
		  elf_link_hash_lookup (&htab->elf, p, FALSE, FALSE, FALSE);
	    }
	  if (fh != NULL)
	    {
	      eh->oh = fh;
	      fh->oh = eh;
	    }
	}
      if (fh != NULL)
	_bfd_elf_link_hash_hide_symbol (info, &fh->elf, force_local);
    }
}