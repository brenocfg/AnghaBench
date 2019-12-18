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
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct string_hash_entry {TYPE_3__ root; struct string_hash_entry* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct stab_write_handle {int symbols_size; int symbols_alloc; int strings_size; int type_index; int so_offset; int fun_offset; scalar_t__ pending_lbrac; struct string_hash_entry* strings; int /*<<< orphan*/ * symbols; scalar_t__ last_text_address; scalar_t__ fnaddr; scalar_t__ nesting; int /*<<< orphan*/  type_cache; int /*<<< orphan*/ * type_stack; TYPE_2__ typedef_hash; TYPE_1__ strhash; int /*<<< orphan*/ * last_string; int /*<<< orphan*/ * abfd; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_SO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char const* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_hash_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_write (void*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  non_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stab_fns ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_hash_newfunc ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
write_stabs_in_sections_debugging_info (bfd *abfd, void *dhandle,
					bfd_byte **psyms,
					bfd_size_type *psymsize,
					bfd_byte **pstrings,
					bfd_size_type *pstringsize)
{
  struct stab_write_handle info;
  struct string_hash_entry *h;
  bfd_byte *p;

  info.abfd = abfd;

  info.symbols_size = 0;
  info.symbols_alloc = 500;
  info.symbols = (bfd_byte *) xmalloc (info.symbols_alloc);

  info.strings = NULL;
  info.last_string = NULL;
  /* Reserve 1 byte for a null byte.  */
  info.strings_size = 1;

  if (!bfd_hash_table_init (&info.strhash.table, string_hash_newfunc,
			    sizeof (struct string_hash_entry))
      || !bfd_hash_table_init (&info.typedef_hash.table, string_hash_newfunc,
			       sizeof (struct string_hash_entry)))
    {
      non_fatal ("bfd_hash_table_init_failed: %s",
		 bfd_errmsg (bfd_get_error ()));
      return FALSE;
    }

  info.type_stack = NULL;
  info.type_index = 1;
  memset (&info.type_cache, 0, sizeof info.type_cache);
  info.so_offset = -1;
  info.fun_offset = -1;
  info.last_text_address = 0;
  info.nesting = 0;
  info.fnaddr = 0;
  info.pending_lbrac = (bfd_vma) -1;

  /* The initial symbol holds the string size.  */
  if (! stab_write_symbol (&info, 0, 0, 0, (const char *) NULL))
    return FALSE;

  /* Output an initial N_SO symbol.  */
  info.so_offset = info.symbols_size;
  if (! stab_write_symbol (&info, N_SO, 0, 0, bfd_get_filename (abfd)))
    return FALSE;

  if (! debug_write (dhandle, &stab_fns, (void *) &info))
    return FALSE;

  assert (info.pending_lbrac == (bfd_vma) -1);

  /* Output a trailing N_SO.  */
  if (! stab_write_symbol (&info, N_SO, 0, info.last_text_address,
			   (const char *) NULL))
    return FALSE;

  /* Put the string size in the initial symbol.  */
  bfd_put_32 (abfd, info.strings_size, info.symbols + 8);

  *psyms = info.symbols;
  *psymsize = info.symbols_size;

  *pstringsize = info.strings_size;
  *pstrings = (bfd_byte *) xmalloc (info.strings_size);

  p = *pstrings;
  *p++ = '\0';
  for (h = info.strings; h != NULL; h = h->next)
    {
      strcpy ((char *) p, h->root.string);
      p += strlen ((char *) p) + 1;
    }

  return TRUE;
}