#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct external_nlist {int /*<<< orphan*/  e_value; int /*<<< orphan*/  e_strx; int /*<<< orphan*/  e_type; } ;
struct bfd_link_info {int common_skip_ar_aymbols; TYPE_4__* callbacks; TYPE_5__* hash; } ;
struct TYPE_9__ {scalar_t__ size; TYPE_6__* p; } ;
struct TYPE_8__ {int /*<<< orphan*/ * abfd; } ;
struct TYPE_10__ {TYPE_2__ c; TYPE_1__ undef; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_3__ u; } ;
struct bfd_link_hash_common_entry {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_14__ {unsigned int section_align_power; } ;
struct TYPE_13__ {unsigned int alignment_power; int /*<<< orphan*/  section; } ;
struct TYPE_12__ {int /*<<< orphan*/  table; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* add_archive_element ) (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int H_GET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int N_ABS ; 
 int N_BSS ; 
 int N_DATA ; 
 int N_EXT ; 
 int N_FN ; 
 int N_INDR ; 
 int N_STAB ; 
 int N_TEXT ; 
 int N_UNDF ; 
 int N_WARNING ; 
 int N_WEAKA ; 
 int N_WEAKB ; 
 int N_WEAKD ; 
 int N_WEAKT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_7__* bfd_get_arch_info (int /*<<< orphan*/ *) ; 
 TYPE_6__* bfd_hash_allocate (int /*<<< orphan*/ *,int) ; 
#define  bfd_link_common_skip_all 130 
#define  bfd_link_common_skip_data 129 
#define  bfd_link_common_skip_text 128 
 scalar_t__ bfd_link_hash_common ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_undefined ; 
 unsigned int bfd_log2 (scalar_t__) ; 
 int /*<<< orphan*/  bfd_make_section_old_way (int /*<<< orphan*/ *,char*) ; 
 char* obj_aout_external_strings (int /*<<< orphan*/ *) ; 
 int obj_aout_external_sym_count (int /*<<< orphan*/ *) ; 
 struct external_nlist* obj_aout_external_syms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub2 (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub3 (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bfd_boolean
aout_link_check_ar_symbols (bfd *abfd,
			    struct bfd_link_info *info,
			    bfd_boolean *pneeded)
{
  struct external_nlist *p;
  struct external_nlist *pend;
  char *strings;

  *pneeded = FALSE;

  /* Look through all the symbols.  */
  p = obj_aout_external_syms (abfd);
  pend = p + obj_aout_external_sym_count (abfd);
  strings = obj_aout_external_strings (abfd);
  for (; p < pend; p++)
    {
      int type = H_GET_8 (abfd, p->e_type);
      const char *name;
      struct bfd_link_hash_entry *h;

      /* Ignore symbols that are not externally visible.  This is an
	 optimization only, as we check the type more thoroughly
	 below.  */
      if (((type & N_EXT) == 0
	   || (type & N_STAB) != 0
	   || type == N_FN)
	  && type != N_WEAKA
	  && type != N_WEAKT
	  && type != N_WEAKD
	  && type != N_WEAKB)
	{
	  if (type == N_WARNING
	      || type == N_INDR)
	    ++p;
	  continue;
	}

      name = strings + GET_WORD (abfd, p->e_strx);
      h = bfd_link_hash_lookup (info->hash, name, FALSE, FALSE, TRUE);

      /* We are only interested in symbols that are currently
	 undefined or common.  */
      if (h == NULL
	  || (h->type != bfd_link_hash_undefined
	      && h->type != bfd_link_hash_common))
	{
	  if (type == (N_INDR | N_EXT))
	    ++p;
	  continue;
	}

      if (type == (N_TEXT | N_EXT)
	  || type == (N_DATA | N_EXT)
	  || type == (N_BSS | N_EXT)
	  || type == (N_ABS | N_EXT)
	  || type == (N_INDR | N_EXT))
	{
	  /* This object file defines this symbol.  We must link it
	     in.  This is true regardless of whether the current
	     definition of the symbol is undefined or common.

             If the current definition is common, we have a case in
	     which we have already seen an object file including:
	         int a;
	     and this object file from the archive includes:
	         int a = 5;
	     In such a case, whether to include this object is target
             dependant for backward compatibility.

	     FIXME: The SunOS 4.1.3 linker will pull in the archive
	     element if the symbol is defined in the .data section,
	     but not if it is defined in the .text section.  That
	     seems a bit crazy to me, and it has not been implemented
	     yet.  However, it might be correct.  */
	  if (h->type == bfd_link_hash_common)
	    {
	      int skip = 0;

	      switch (info->common_skip_ar_aymbols)
		{
		case bfd_link_common_skip_text:
		  skip = (type == (N_TEXT | N_EXT));
		  break;
		case bfd_link_common_skip_data:
		  skip = (type == (N_DATA | N_EXT));
		  break;
		default:
		case bfd_link_common_skip_all:
		  skip = 1;
		  break;
		}

	      if (skip)
		continue;
	    }

	  if (! (*info->callbacks->add_archive_element) (info, abfd, name))
	    return FALSE;
	  *pneeded = TRUE;
	  return TRUE;
	}

      if (type == (N_UNDF | N_EXT))
	{
	  bfd_vma value;

	  value = GET_WORD (abfd, p->e_value);
	  if (value != 0)
	    {
	      /* This symbol is common in the object from the archive
		 file.  */
	      if (h->type == bfd_link_hash_undefined)
		{
		  bfd *symbfd;
		  unsigned int power;

		  symbfd = h->u.undef.abfd;
		  if (symbfd == NULL)
		    {
		      /* This symbol was created as undefined from
			 outside BFD.  We assume that we should link
			 in the object file.  This is done for the -u
			 option in the linker.  */
		      if (! (*info->callbacks->add_archive_element) (info,
								     abfd,
								     name))
			return FALSE;
		      *pneeded = TRUE;
		      return TRUE;
		    }
		  /* Turn the current link symbol into a common
		     symbol.  It is already on the undefs list.  */
		  h->type = bfd_link_hash_common;
		  h->u.c.p = bfd_hash_allocate (&info->hash->table,
						sizeof (struct bfd_link_hash_common_entry));
		  if (h->u.c.p == NULL)
		    return FALSE;

		  h->u.c.size = value;

		  /* FIXME: This isn't quite right.  The maximum
		     alignment of a common symbol should be set by the
		     architecture of the output file, not of the input
		     file.  */
		  power = bfd_log2 (value);
		  if (power > bfd_get_arch_info (abfd)->section_align_power)
		    power = bfd_get_arch_info (abfd)->section_align_power;
		  h->u.c.p->alignment_power = power;

		  h->u.c.p->section = bfd_make_section_old_way (symbfd,
								"COMMON");
		}
	      else
		{
		  /* Adjust the size of the common symbol if
		     necessary.  */
		  if (value > h->u.c.size)
		    h->u.c.size = value;
		}
	    }
	}

      if (type == N_WEAKA
	  || type == N_WEAKT
	  || type == N_WEAKD
	  || type == N_WEAKB)
	{
	  /* This symbol is weak but defined.  We must pull it in if
	     the current link symbol is undefined, but we don't want
	     it if the current link symbol is common.  */
	  if (h->type == bfd_link_hash_undefined)
	    {
	      if (! (*info->callbacks->add_archive_element) (info, abfd, name))
		return FALSE;
	      *pneeded = TRUE;
	      return TRUE;
	    }
	}
    }

  /* We do not need this object file.  */
  return TRUE;
}