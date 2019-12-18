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
struct string_hash_entry {int index; struct string_hash_entry* next; } ;
struct stab_write_handle {int strings_size; int symbols_size; int symbols_alloc; int /*<<< orphan*/ * symbols; int /*<<< orphan*/  abfd; struct string_hash_entry* last_string; struct string_hash_entry* strings; int /*<<< orphan*/  strhash; } ;
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int STAB_SYMBOL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct string_hash_entry* string_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bfd_boolean
stab_write_symbol (struct stab_write_handle *info, int type, int desc,
		   bfd_vma value, const char *string)
{
  bfd_size_type strx;
  bfd_byte sym[STAB_SYMBOL_SIZE];

  if (string == NULL)
    strx = 0;
  else
    {
      struct string_hash_entry *h;

      h = string_hash_lookup (&info->strhash, string, TRUE, TRUE);
      if (h == NULL)
	{
	  non_fatal (_("string_hash_lookup failed: %s"),
		     bfd_errmsg (bfd_get_error ()));
	  return FALSE;
	}
      if (h->index != -1)
	strx = h->index;
      else
	{
	  strx = info->strings_size;
	  h->index = strx;
	  if (info->last_string == NULL)
	    info->strings = h;
	  else
	    info->last_string->next = h;
	  info->last_string = h;
	  info->strings_size += strlen (string) + 1;
	}
    }

  /* This presumes 32 bit values.  */
  bfd_put_32 (info->abfd, strx, sym);
  bfd_put_8 (info->abfd, type, sym + 4);
  bfd_put_8 (info->abfd, 0, sym + 5);
  bfd_put_16 (info->abfd, desc, sym + 6);
  bfd_put_32 (info->abfd, value, sym + 8);

  if (info->symbols_size + STAB_SYMBOL_SIZE > info->symbols_alloc)
    {
      info->symbols_alloc *= 2;
      info->symbols = (bfd_byte *) xrealloc (info->symbols,
					     info->symbols_alloc);
    }

  memcpy (info->symbols + info->symbols_size, sym, STAB_SYMBOL_SIZE);

  info->symbols_size += STAB_SYMBOL_SIZE;

  return TRUE;
}