#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_5__* section; } ;
struct TYPE_14__ {TYPE_1__ indirect; } ;
struct bfd_link_order {int offset; scalar_t__ size; TYPE_2__ u; } ;
struct bfd_link_info {int /*<<< orphan*/  relocatable; int /*<<< orphan*/  hash; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_15__ {struct bfd_link_hash_entry* p; } ;
struct TYPE_16__ {int flags; TYPE_3__ udata; } ;
typedef  TYPE_4__ asymbol ;
struct TYPE_17__ {int flags; scalar_t__ size; int output_offset; scalar_t__ reloc_count; scalar_t__ rawsize; int /*<<< orphan*/ * orelocation; struct TYPE_17__* output_section; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_5__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BSF_CONSTRUCTOR ; 
 int BSF_GLOBAL ; 
 int BSF_INDIRECT ; 
 int BSF_WARNING ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__** _bfd_generic_link_get_symbols (int /*<<< orphan*/ *) ; 
 int _bfd_generic_link_get_symcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_asymbol_name (TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/ * bfd_get_relocated_section_contents (int /*<<< orphan*/ *,struct bfd_link_info*,struct bfd_link_order*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  bfd_get_section (TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_ind_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ ) ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_malloc (scalar_t__) ; 
 int bfd_octets_per_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int,scalar_t__) ; 
 struct bfd_link_hash_entry* bfd_wrapped_link_hash_lookup (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_link_read_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_symbol_from_hash (TYPE_4__*,struct bfd_link_hash_entry*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
default_indirect_link_order (bfd *output_bfd,
			     struct bfd_link_info *info,
			     asection *output_section,
			     struct bfd_link_order *link_order,
			     bfd_boolean generic_linker)
{
  asection *input_section;
  bfd *input_bfd;
  bfd_byte *contents = NULL;
  bfd_byte *new_contents;
  bfd_size_type sec_size;
  file_ptr loc;

  BFD_ASSERT ((output_section->flags & SEC_HAS_CONTENTS) != 0);

  input_section = link_order->u.indirect.section;
  input_bfd = input_section->owner;
  if (input_section->size == 0)
    return TRUE;

  BFD_ASSERT (input_section->output_section == output_section);
  BFD_ASSERT (input_section->output_offset == link_order->offset);
  BFD_ASSERT (input_section->size == link_order->size);

  if (info->relocatable
      && input_section->reloc_count > 0
      && output_section->orelocation == NULL)
    {
      /* Space has not been allocated for the output relocations.
	 This can happen when we are called by a specific backend
	 because somebody is attempting to link together different
	 types of object files.  Handling this case correctly is
	 difficult, and sometimes impossible.  */
      (*_bfd_error_handler)
	(_("Attempt to do relocatable link with %s input and %s output"),
	 bfd_get_target (input_bfd), bfd_get_target (output_bfd));
      bfd_set_error (bfd_error_wrong_format);
      return FALSE;
    }

  if (! generic_linker)
    {
      asymbol **sympp;
      asymbol **symppend;

      /* Get the canonical symbols.  The generic linker will always
	 have retrieved them by this point, but we are being called by
	 a specific linker, presumably because we are linking
	 different types of object files together.  */
      if (! generic_link_read_symbols (input_bfd))
	return FALSE;

      /* Since we have been called by a specific linker, rather than
	 the generic linker, the values of the symbols will not be
	 right.  They will be the values as seen in the input file,
	 not the values of the final link.  We need to fix them up
	 before we can relocate the section.  */
      sympp = _bfd_generic_link_get_symbols (input_bfd);
      symppend = sympp + _bfd_generic_link_get_symcount (input_bfd);
      for (; sympp < symppend; sympp++)
	{
	  asymbol *sym;
	  struct bfd_link_hash_entry *h;

	  sym = *sympp;

	  if ((sym->flags & (BSF_INDIRECT
			     | BSF_WARNING
			     | BSF_GLOBAL
			     | BSF_CONSTRUCTOR
			     | BSF_WEAK)) != 0
	      || bfd_is_und_section (bfd_get_section (sym))
	      || bfd_is_com_section (bfd_get_section (sym))
	      || bfd_is_ind_section (bfd_get_section (sym)))
	    {
	      /* sym->udata may have been set by
		 generic_link_add_symbol_list.  */
	      if (sym->udata.p != NULL)
		h = sym->udata.p;
	      else if (bfd_is_und_section (bfd_get_section (sym)))
		h = bfd_wrapped_link_hash_lookup (output_bfd, info,
						  bfd_asymbol_name (sym),
						  FALSE, FALSE, TRUE);
	      else
		h = bfd_link_hash_lookup (info->hash,
					  bfd_asymbol_name (sym),
					  FALSE, FALSE, TRUE);
	      if (h != NULL)
		set_symbol_from_hash (sym, h);
	    }
	}
    }

  /* Get and relocate the section contents.  */
  sec_size = (input_section->rawsize > input_section->size
	      ? input_section->rawsize
	      : input_section->size);
  contents = bfd_malloc (sec_size);
  if (contents == NULL && sec_size != 0)
    goto error_return;
  new_contents = (bfd_get_relocated_section_contents
		  (output_bfd, info, link_order, contents, info->relocatable,
		   _bfd_generic_link_get_symbols (input_bfd)));
  if (!new_contents)
    goto error_return;

  /* Output the section contents.  */
  loc = input_section->output_offset * bfd_octets_per_byte (output_bfd);
  if (! bfd_set_section_contents (output_bfd, output_section,
				  new_contents, loc, input_section->size))
    goto error_return;

  if (contents != NULL)
    free (contents);
  return TRUE;

 error_return:
  if (contents != NULL)
    free (contents);
  return FALSE;
}