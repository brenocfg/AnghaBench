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
struct elf_link_hash_table {int /*<<< orphan*/  dynobj; } ;
struct elf_link_hash_entry {int dynindx; int /*<<< orphan*/  type; int /*<<< orphan*/  other; scalar_t__ forced_local; int /*<<< orphan*/  def_regular; } ;
struct elf_backend_data {int /*<<< orphan*/  (* is_function_type ) (int /*<<< orphan*/ ) ;} ;
struct bfd_link_info {scalar_t__ executable; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ ELF_COMMON_DEF_P (struct elf_link_hash_entry*) ; 
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ STV_PROTECTED ; 
 scalar_t__ SYMBOLIC_BIND (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  TRUE ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_elf_hash_table (struct elf_link_hash_table*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_elf_symbol_refs_local_p (struct elf_link_hash_entry *h,
			      struct bfd_link_info *info,
			      bfd_boolean local_protected)
{
  const struct elf_backend_data *bed;
  struct elf_link_hash_table *hash_table;

  /* If it's a local sym, of course we resolve locally.  */
  if (h == NULL)
    return TRUE;

  /* Common symbols that become definitions don't get the DEF_REGULAR
     flag set, so test it first, and don't bail out.  */
  if (ELF_COMMON_DEF_P (h))
    /* Do nothing.  */;
  /* If we don't have a definition in a regular file, then we can't
     resolve locally.  The sym is either undefined or dynamic.  */
  else if (!h->def_regular)
    return FALSE;

  /* Forced local symbols resolve locally.  */
  if (h->forced_local)
    return TRUE;

  /* As do non-dynamic symbols.  */
  if (h->dynindx == -1)
    return TRUE;

  /* At this point, we know the symbol is defined and dynamic.  In an
     executable it must resolve locally, likewise when building symbolic
     shared libraries.  */
  if (info->executable || SYMBOLIC_BIND (info, h))
    return TRUE;

  /* Now deal with defined dynamic symbols in shared libraries.  Ones
     with default visibility might not resolve locally.  */
  if (ELF_ST_VISIBILITY (h->other) == STV_DEFAULT)
    return FALSE;

  /* However, STV_HIDDEN or STV_INTERNAL ones must be local.  */
  if (ELF_ST_VISIBILITY (h->other) != STV_PROTECTED)
    return TRUE;

  hash_table = elf_hash_table (info);
  if (!is_elf_hash_table (hash_table))
    return TRUE;

  bed = get_elf_backend_data (hash_table->dynobj);

  /* STV_PROTECTED non-function symbols are local.  */
  if (!bed->is_function_type (h->type))
    return TRUE;

  /* Function pointer equality tests may require that STV_PROTECTED
     symbols be treated as dynamic symbols, even when we know that the
     dynamic linker will resolve them locally.  */
  return local_protected;
}