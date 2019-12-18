#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct external_exec {int dummy; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_16__ {int a_syms; int a_trsize; int a_drsize; int /*<<< orphan*/  a_dload; int /*<<< orphan*/  a_tload; int /*<<< orphan*/  a_balign; int /*<<< orphan*/  a_dalign; int /*<<< orphan*/  a_talign; int /*<<< orphan*/  a_entry; int /*<<< orphan*/  a_bss; int /*<<< orphan*/  a_data; int /*<<< orphan*/  a_text; int /*<<< orphan*/  a_info; } ;
struct TYPE_15__ {int /*<<< orphan*/  alignment_power; int /*<<< orphan*/  size; } ;
struct TYPE_14__ {int reloc_count; int /*<<< orphan*/  vma; int /*<<< orphan*/  alignment_power; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAGIC ; 
 int BSF_DEBUGGING ; 
 scalar_t__ EXEC_BYTES_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ N_DROFF (TYPE_6__) ; 
 scalar_t__ N_SYMOFF (TYPE_6__) ; 
 scalar_t__ N_TROFF (TYPE_6__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aout_32_make_sections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_32_write_syms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b_out_squirt_out_relocs (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  b_out_symbol_cmp ; 
 scalar_t__ bfd_bwrite (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__** bfd_get_outsymbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_start_address (int /*<<< orphan*/ *) ; 
 int bfd_get_symcount (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bout_swap_exec_header_out (int /*<<< orphan*/ *,TYPE_6__*,struct external_exec*) ; 
 TYPE_6__* exec_hdr (int /*<<< orphan*/ *) ; 
 TYPE_5__* obj_bsssec (int /*<<< orphan*/ *) ; 
 TYPE_3__* obj_datasec (int /*<<< orphan*/ *) ; 
 TYPE_3__* obj_textsec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
b_out_write_object_contents (bfd *abfd)
{
  struct external_exec swapped_hdr;
  bfd_size_type amt;

  if (! aout_32_make_sections (abfd))
    return FALSE;

  exec_hdr (abfd)->a_info = BMAGIC;

  exec_hdr (abfd)->a_text = obj_textsec (abfd)->size;
  exec_hdr (abfd)->a_data = obj_datasec (abfd)->size;
  exec_hdr (abfd)->a_bss = obj_bsssec (abfd)->size;
  exec_hdr (abfd)->a_syms = bfd_get_symcount (abfd) * 12;
  exec_hdr (abfd)->a_entry = bfd_get_start_address (abfd);
  exec_hdr (abfd)->a_trsize = (obj_textsec (abfd)->reloc_count) * 8;
  exec_hdr (abfd)->a_drsize = (obj_datasec (abfd)->reloc_count) * 8;

  exec_hdr (abfd)->a_talign = obj_textsec (abfd)->alignment_power;
  exec_hdr (abfd)->a_dalign = obj_datasec (abfd)->alignment_power;
  exec_hdr (abfd)->a_balign = obj_bsssec (abfd)->alignment_power;

  exec_hdr (abfd)->a_tload = obj_textsec (abfd)->vma;
  exec_hdr (abfd)->a_dload = obj_datasec (abfd)->vma;

  bout_swap_exec_header_out (abfd, exec_hdr (abfd), &swapped_hdr);

  amt = EXEC_BYTES_SIZE;
  if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0
      || bfd_bwrite ((void *) &swapped_hdr, amt, abfd) != amt)
    return FALSE;

  /* Now write out reloc info, followed by syms and strings */
  if (bfd_get_symcount (abfd) != 0)
    {
      /* Make sure {CALL,BAL}NAME symbols remain adjacent on output
	 by sorting.  This is complicated by the fact that stabs are
	 also ordered.  Solve this by shifting all stabs to the end
	 in order, then sorting the rest.  */

      asymbol **outsyms, **p, **q;

      outsyms = bfd_get_outsymbols (abfd);
      p = outsyms + bfd_get_symcount (abfd);

      for (q = p--; p >= outsyms; p--)
	{
	  if ((*p)->flags & BSF_DEBUGGING)
	    {
	      asymbol *t = *--q;
	      *q = *p;
	      *p = t;
	    }
	}

      if (q > outsyms)
	qsort (outsyms, (size_t) (q - outsyms), sizeof (asymbol*),
	       b_out_symbol_cmp);

      /* Back to your regularly scheduled program.  */
      if (bfd_seek (abfd, (file_ptr) (N_SYMOFF (*exec_hdr (abfd))), SEEK_SET)
	  != 0)
	return FALSE;

      if (! aout_32_write_syms (abfd))
	return FALSE;

      if (bfd_seek (abfd, (file_ptr) (N_TROFF (*exec_hdr (abfd))), SEEK_SET)
	  != 0)
	return FALSE;

      if (!b_out_squirt_out_relocs (abfd, obj_textsec (abfd)))
	return FALSE;
      if (bfd_seek (abfd, (file_ptr) (N_DROFF (*exec_hdr (abfd))), SEEK_SET)
	  != 0)
	return FALSE;

      if (!b_out_squirt_out_relocs (abfd, obj_datasec (abfd)))
	return FALSE;
    }
  return TRUE;
}