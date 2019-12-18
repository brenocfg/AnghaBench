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
struct elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char ELF_VER_CHR ; 
 int /*<<< orphan*/  FALSE ; 
 char* bfd_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bfd_release (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  elf_hash_table (struct bfd_link_info*) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

struct elf_link_hash_entry *
_bfd_elf_archive_symbol_lookup (bfd *abfd,
				struct bfd_link_info *info,
				const char *name)
{
  struct elf_link_hash_entry *h;
  char *p, *copy;
  size_t len, first;

  h = elf_link_hash_lookup (elf_hash_table (info), name, FALSE, FALSE, FALSE);
  if (h != NULL)
    return h;

  /* If this is a default version (the name contains @@), look up the
     symbol again with only one `@' as well as without the version.
     The effect is that references to the symbol with and without the
     version will be matched by the default symbol in the archive.  */

  p = strchr (name, ELF_VER_CHR);
  if (p == NULL || p[1] != ELF_VER_CHR)
    return h;

  /* First check with only one `@'.  */
  len = strlen (name);
  copy = bfd_alloc (abfd, len);
  if (copy == NULL)
    return (struct elf_link_hash_entry *)(intptr_t)-1;

  first = p - name + 1;
  memcpy (copy, name, first);
  memcpy (copy + first, name + first + 1, len - first);

  h = elf_link_hash_lookup (elf_hash_table (info), copy, FALSE, FALSE, FALSE);
  if (h == NULL)
    {
      /* We also need to check references to the symbol without the
	 version.  */
      copy[first - 1] = '\0';
      h = elf_link_hash_lookup (elf_hash_table (info), copy,
				FALSE, FALSE, FALSE);
    }

  bfd_release (abfd, copy);
  return h;
}