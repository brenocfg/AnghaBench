#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xcoff_link_hash_entry {int flags; } ;
struct TYPE_5__ {scalar_t__ _l_zeroes; int _l_offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  _l_name; TYPE_1__ _l_l; } ;
struct internal_ldsym {int l_smtype; TYPE_2__ _l; } ;
struct internal_ldhdr {int l_stoff; int l_nsyms; } ;
struct bfd_link_info {TYPE_3__* callbacks; int /*<<< orphan*/  hash; } ;
struct bfd_link_hash_entry {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_8__ {int /*<<< orphan*/ * contents; int /*<<< orphan*/  keep_contents; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* add_archive_element ) (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int L_EXPORT ; 
 int SYMNMLEN ; 
 int /*<<< orphan*/  TRUE ; 
 int XCOFF_DEF_DYNAMIC ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_undefined ; 
 int bfd_xcoff_ldsymsz (int /*<<< orphan*/ *) ; 
 int bfd_xcoff_loader_symbol_offset (int /*<<< orphan*/ *,struct internal_ldhdr*) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldhdr_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct internal_ldhdr*) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldsym_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct internal_ldsym*) ; 
 TYPE_4__* coff_section_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xcoff_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
xcoff_link_check_dynamic_ar_symbols (bfd *abfd,
				     struct bfd_link_info *info,
				     bfd_boolean *pneeded)
{
  asection *lsec;
  bfd_byte *contents;
  struct internal_ldhdr ldhdr;
  const char *strings;
  bfd_byte *elsym, *elsymend;

  *pneeded = FALSE;

  lsec = bfd_get_section_by_name (abfd, ".loader");
  if (lsec == NULL)
    /* There are no symbols, so don't try to include it.  */
    return TRUE;

  if (! xcoff_get_section_contents (abfd, lsec))
    return FALSE;
  contents = coff_section_data (abfd, lsec)->contents;

  bfd_xcoff_swap_ldhdr_in (abfd, contents, &ldhdr);

  strings = (char *) contents + ldhdr.l_stoff;

  elsym = contents + bfd_xcoff_loader_symbol_offset (abfd, &ldhdr);

  elsymend = elsym + ldhdr.l_nsyms * bfd_xcoff_ldsymsz (abfd);
  for (; elsym < elsymend; elsym += bfd_xcoff_ldsymsz (abfd))
    {
      struct internal_ldsym ldsym;
      char nambuf[SYMNMLEN + 1];
      const char *name;
      struct bfd_link_hash_entry *h;

      bfd_xcoff_swap_ldsym_in (abfd, elsym, &ldsym);

      /* We are only interested in exported symbols.  */
      if ((ldsym.l_smtype & L_EXPORT) == 0)
	continue;

      if (ldsym._l._l_l._l_zeroes == 0)
	name = strings + ldsym._l._l_l._l_offset;
      else
	{
	  memcpy (nambuf, ldsym._l._l_name, SYMNMLEN);
	  nambuf[SYMNMLEN] = '\0';
	  name = nambuf;
	}

      h = bfd_link_hash_lookup (info->hash, name, FALSE, FALSE, TRUE);

      /* We are only interested in symbols that are currently
	 undefined.  At this point we know that we are using an XCOFF
	 hash table.  */
      if (h != NULL
	  && h->type == bfd_link_hash_undefined
	  && (((struct xcoff_link_hash_entry *) h)->flags
	      & XCOFF_DEF_DYNAMIC) == 0)
	{
	  if (! (*info->callbacks->add_archive_element) (info, abfd, name))
	    return FALSE;
	  *pneeded = TRUE;
	  return TRUE;
	}
    }

  /* We do not need this shared object.  */
  if (contents != NULL && ! coff_section_data (abfd, lsec)->keep_contents)
    {
      free (coff_section_data (abfd, lsec)->contents);
      coff_section_data (abfd, lsec)->contents = NULL;
    }

  return TRUE;
}