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
struct TYPE_3__ {scalar_t__ ld_buckets; scalar_t__ ld_stab; scalar_t__ ld_hash; scalar_t__ ld_symb_size; } ;
struct sunos_dynamic_info {scalar_t__ dynsym_count; int /*<<< orphan*/ * canonical_dynsym; scalar_t__ dynstr; TYPE_2__* dynsym; TYPE_1__ dyninfo; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  aout_symbol_type ;
struct TYPE_4__ {int /*<<< orphan*/ * e_strx; } ;

/* Variables and functions */
 int BYTES_IN_WORD ; 
 scalar_t__ GET_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long HASH_ENTRY_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  aout_32_translate_symbol_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ bfd_bread (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_malloc (scalar_t__) ; 
 int /*<<< orphan*/  bfd_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ obj_aout_dynamic_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunos_slurp_dynamic_symtab (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
sunos_canonicalize_dynamic_symtab (bfd *abfd, asymbol **storage)
{
  struct sunos_dynamic_info *info;
  unsigned long i;

  if (! sunos_slurp_dynamic_symtab (abfd))
    return -1;

  info = (struct sunos_dynamic_info *) obj_aout_dynamic_info (abfd);

#ifdef CHECK_DYNAMIC_HASH
  /* Check my understanding of the dynamic hash table by making sure
     that each symbol can be located in the hash table.  */
  {
    bfd_size_type table_size;
    bfd_byte *table;
    bfd_size_type i;

    if (info->dyninfo.ld_buckets > info->dynsym_count)
      abort ();
    table_size = info->dyninfo.ld_stab - info->dyninfo.ld_hash;
    table = bfd_malloc (table_size);
    if (table == NULL && table_size != 0)
      abort ();
    if (bfd_seek (abfd, (file_ptr) info->dyninfo.ld_hash, SEEK_SET) != 0
	|| bfd_bread ((void *) table, table_size, abfd) != table_size)
      abort ();
    for (i = 0; i < info->dynsym_count; i++)
      {
	unsigned char *name;
	unsigned long hash;

	name = ((unsigned char *) info->dynstr
		+ GET_WORD (abfd, info->dynsym[i].e_strx));
	hash = 0;
	while (*name != '\0')
	  hash = (hash << 1) + *name++;
	hash &= 0x7fffffff;
	hash %= info->dyninfo.ld_buckets;
	while (GET_WORD (abfd, table + hash * HASH_ENTRY_SIZE) != i)
	  {
	    hash = GET_WORD (abfd,
			     table + hash * HASH_ENTRY_SIZE + BYTES_IN_WORD);
	    if (hash == 0 || hash >= table_size / HASH_ENTRY_SIZE)
	      abort ();
	  }
      }
    free (table);
  }
#endif /* CHECK_DYNAMIC_HASH */

  /* Get the asymbol structures corresponding to the dynamic nlist
     structures.  */
  if (info->canonical_dynsym == NULL)
    {
      bfd_size_type size;
      bfd_size_type strsize = info->dyninfo.ld_symb_size;

      size = (bfd_size_type) info->dynsym_count * sizeof (aout_symbol_type);
      info->canonical_dynsym = bfd_alloc (abfd, size);
      if (info->canonical_dynsym == NULL && info->dynsym_count != 0)
	return -1;

      if (! aout_32_translate_symbol_table (abfd, info->canonical_dynsym,
					    info->dynsym,
					    (bfd_size_type) info->dynsym_count,
					    info->dynstr, strsize, TRUE))
	{
	  if (info->canonical_dynsym != NULL)
	    {
	      bfd_release (abfd, info->canonical_dynsym);
	      info->canonical_dynsym = NULL;
	    }
	  return -1;
	}
    }

  /* Return pointers to the dynamic asymbol structures.  */
  for (i = 0; i < info->dynsym_count; i++)
    *storage++ = (asymbol *) (info->canonical_dynsym + i);
  *storage = NULL;

  return info->dynsym_count;
}