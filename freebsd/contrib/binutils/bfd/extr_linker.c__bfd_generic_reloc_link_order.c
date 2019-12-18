#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct generic_link_hash_entry {int /*<<< orphan*/  sym; int /*<<< orphan*/  written; } ;
struct TYPE_19__ {TYPE_3__* p; } ;
struct TYPE_20__ {TYPE_4__ reloc; } ;
struct bfd_link_order {int offset; scalar_t__ type; TYPE_5__ u; } ;
struct bfd_link_info {TYPE_1__* callbacks; int /*<<< orphan*/  relocatable; } ;
typedef  int file_ptr ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_21__ {size_t reloc_count; TYPE_7__** orelocation; } ;
typedef  TYPE_6__ asection ;
struct TYPE_22__ {int address; scalar_t__ addend; TYPE_10__* howto; int /*<<< orphan*/ * sym_ptr_ptr; } ;
typedef  TYPE_7__ arelent ;
struct TYPE_23__ {int /*<<< orphan*/ * symbol_ptr_ptr; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; TYPE_9__* section; } ;
struct TYPE_18__ {scalar_t__ addend; TYPE_2__ u; int /*<<< orphan*/  reloc; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* reloc_overflow ) (struct bfd_link_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* unattached_reloc ) (struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  partial_inplace; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int _bfd_relocate_contents (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_7__* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/  bfd_get_reloc_size (TYPE_10__*) ; 
 int bfd_octets_per_byte (int /*<<< orphan*/ *) ; 
#define  bfd_reloc_ok 130 
#define  bfd_reloc_outofrange 129 
#define  bfd_reloc_overflow 128 
 TYPE_10__* bfd_reloc_type_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ *,TYPE_9__*) ; 
 scalar_t__ bfd_section_reloc_link_order ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_wrapped_link_hash_lookup (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_zmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bfd_link_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_generic_reloc_link_order (bfd *abfd,
			       struct bfd_link_info *info,
			       asection *sec,
			       struct bfd_link_order *link_order)
{
  arelent *r;

  if (! info->relocatable)
    abort ();
  if (sec->orelocation == NULL)
    abort ();

  r = bfd_alloc (abfd, sizeof (arelent));
  if (r == NULL)
    return FALSE;

  r->address = link_order->offset;
  r->howto = bfd_reloc_type_lookup (abfd, link_order->u.reloc.p->reloc);
  if (r->howto == 0)
    {
      bfd_set_error (bfd_error_bad_value);
      return FALSE;
    }

  /* Get the symbol to use for the relocation.  */
  if (link_order->type == bfd_section_reloc_link_order)
    r->sym_ptr_ptr = link_order->u.reloc.p->u.section->symbol_ptr_ptr;
  else
    {
      struct generic_link_hash_entry *h;

      h = ((struct generic_link_hash_entry *)
	   bfd_wrapped_link_hash_lookup (abfd, info,
					 link_order->u.reloc.p->u.name,
					 FALSE, FALSE, TRUE));
      if (h == NULL
	  || ! h->written)
	{
	  if (! ((*info->callbacks->unattached_reloc)
		 (info, link_order->u.reloc.p->u.name, NULL, NULL, 0)))
	    return FALSE;
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      r->sym_ptr_ptr = &h->sym;
    }

  /* If this is an inplace reloc, write the addend to the object file.
     Otherwise, store it in the reloc addend.  */
  if (! r->howto->partial_inplace)
    r->addend = link_order->u.reloc.p->addend;
  else
    {
      bfd_size_type size;
      bfd_reloc_status_type rstat;
      bfd_byte *buf;
      bfd_boolean ok;
      file_ptr loc;

      size = bfd_get_reloc_size (r->howto);
      buf = bfd_zmalloc (size);
      if (buf == NULL)
	return FALSE;
      rstat = _bfd_relocate_contents (r->howto, abfd,
				      (bfd_vma) link_order->u.reloc.p->addend,
				      buf);
      switch (rstat)
	{
	case bfd_reloc_ok:
	  break;
	default:
	case bfd_reloc_outofrange:
	  abort ();
	case bfd_reloc_overflow:
	  if (! ((*info->callbacks->reloc_overflow)
		 (info, NULL,
		  (link_order->type == bfd_section_reloc_link_order
		   ? bfd_section_name (abfd, link_order->u.reloc.p->u.section)
		   : link_order->u.reloc.p->u.name),
		  r->howto->name, link_order->u.reloc.p->addend,
		  NULL, NULL, 0)))
	    {
	      free (buf);
	      return FALSE;
	    }
	  break;
	}
      loc = link_order->offset * bfd_octets_per_byte (abfd);
      ok = bfd_set_section_contents (abfd, sec, buf, loc, size);
      free (buf);
      if (! ok)
	return FALSE;

      r->addend = 0;
    }

  sec->orelocation[sec->reloc_count] = r;
  ++sec->reloc_count;

  return TRUE;
}