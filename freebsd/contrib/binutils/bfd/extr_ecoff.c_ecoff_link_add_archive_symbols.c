#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ecoff_backend_data {int /*<<< orphan*/ * (* get_elt_at_filepos ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct bfd_link_info {TYPE_3__* callbacks; TYPE_1__* hash; } ;
struct TYPE_10__ {struct bfd_link_hash_entry* next; } ;
struct TYPE_11__ {TYPE_4__ undef; } ;
struct TYPE_8__ {char const* string; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_5__ u; TYPE_2__ root; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {scalar_t__ tdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* add_archive_element ) (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ;} ;
struct TYPE_7__ {struct bfd_link_hash_entry* undefs_tail; struct bfd_link_hash_entry* undefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_archive_symbols (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ) ; 
 TYPE_6__* bfd_ardata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_no_armap ; 
 int /*<<< orphan*/  bfd_has_map (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_undefined ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr_next_archived_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 unsigned int ecoff_armap_hash (char const*,unsigned int*,unsigned int,unsigned int) ; 
 struct ecoff_backend_data* ecoff_backend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecoff_link_add_object_symbols (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  ecoff_link_check_archive_element ; 
 scalar_t__ streq (char const*,char const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bfd_boolean
ecoff_link_add_archive_symbols (bfd *abfd, struct bfd_link_info *info)
{
  const struct ecoff_backend_data * const backend = ecoff_backend (abfd);
  const bfd_byte *raw_armap;
  struct bfd_link_hash_entry **pundef;
  unsigned int armap_count;
  unsigned int armap_log;
  unsigned int i;
  const bfd_byte *hashtable;
  const char *stringbase;

  if (! bfd_has_map (abfd))
    {
      /* An empty archive is a special case.  */
      if (bfd_openr_next_archived_file (abfd, NULL) == NULL)
	return TRUE;
      bfd_set_error (bfd_error_no_armap);
      return FALSE;
    }

  /* If we don't have any raw data for this archive, as can happen on
     Irix 4.0.5F, we call the generic routine.
     FIXME: We should be more clever about this, since someday tdata
     may get to something for a generic archive.  */
  raw_armap = (const bfd_byte *) bfd_ardata (abfd)->tdata;
  if (raw_armap == NULL)
    return (_bfd_generic_link_add_archive_symbols
	    (abfd, info, ecoff_link_check_archive_element));

  armap_count = H_GET_32 (abfd, raw_armap);

  armap_log = 0;
  for (i = 1; i < armap_count; i <<= 1)
    armap_log++;
  BFD_ASSERT (i == armap_count);

  hashtable = raw_armap + 4;
  stringbase = (const char *) raw_armap + armap_count * 8 + 8;

  /* Look through the list of undefined symbols.  */
  pundef = &info->hash->undefs;
  while (*pundef != NULL)
    {
      struct bfd_link_hash_entry *h;
      unsigned int hash, rehash = 0;
      unsigned int file_offset;
      const char *name;
      bfd *element;

      h = *pundef;

      /* When a symbol is defined, it is not necessarily removed from
	 the list.  */
      if (h->type != bfd_link_hash_undefined
	  && h->type != bfd_link_hash_common)
	{
	  /* Remove this entry from the list, for general cleanliness
	     and because we are going to look through the list again
	     if we search any more libraries.  We can't remove the
	     entry if it is the tail, because that would lose any
	     entries we add to the list later on.  */
	  if (*pundef != info->hash->undefs_tail)
	    *pundef = (*pundef)->u.undef.next;
	  else
	    pundef = &(*pundef)->u.undef.next;
	  continue;
	}

      /* Native ECOFF linkers do not pull in archive elements merely
	 to satisfy common definitions, so neither do we.  We leave
	 them on the list, though, in case we are linking against some
	 other object format.  */
      if (h->type != bfd_link_hash_undefined)
	{
	  pundef = &(*pundef)->u.undef.next;
	  continue;
	}

      /* Look for this symbol in the archive hash table.  */
      hash = ecoff_armap_hash (h->root.string, &rehash, armap_count,
			       armap_log);

      file_offset = H_GET_32 (abfd, hashtable + (hash * 8) + 4);
      if (file_offset == 0)
	{
	  /* Nothing in this slot.  */
	  pundef = &(*pundef)->u.undef.next;
	  continue;
	}

      name = stringbase + H_GET_32 (abfd, hashtable + (hash * 8));
      if (name[0] != h->root.string[0]
	  || ! streq (name, h->root.string))
	{
	  unsigned int srch;
	  bfd_boolean found;

	  /* That was the wrong symbol.  Try rehashing.  */
	  found = FALSE;
	  for (srch = (hash + rehash) & (armap_count - 1);
	       srch != hash;
	       srch = (srch + rehash) & (armap_count - 1))
	    {
	      file_offset = H_GET_32 (abfd, hashtable + (srch * 8) + 4);
	      if (file_offset == 0)
		break;
	      name = stringbase + H_GET_32 (abfd, hashtable + (srch * 8));
	      if (name[0] == h->root.string[0]
		  && streq (name, h->root.string))
		{
		  found = TRUE;
		  break;
		}
	    }

	  if (! found)
	    {
	      pundef = &(*pundef)->u.undef.next;
	      continue;
	    }

	  hash = srch;
	}

      element = (*backend->get_elt_at_filepos) (abfd, (file_ptr) file_offset);
      if (element == NULL)
	return FALSE;

      if (! bfd_check_format (element, bfd_object))
	return FALSE;

      /* Unlike the generic linker, we know that this element provides
	 a definition for an undefined symbol and we know that we want
	 to include it.  We don't need to check anything.  */
      if (! (*info->callbacks->add_archive_element) (info, element, name))
	return FALSE;
      if (! ecoff_link_add_object_symbols (element, info))
	return FALSE;

      pundef = &(*pundef)->u.undef.next;
    }

  return TRUE;
}