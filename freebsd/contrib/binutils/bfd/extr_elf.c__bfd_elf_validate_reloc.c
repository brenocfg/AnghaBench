#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int bitsize; scalar_t__ pcrel_offset; int /*<<< orphan*/  name; scalar_t__ pc_relative; } ;
typedef  TYPE_3__ reloc_howto_type ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_15__ {scalar_t__ xvec; } ;
typedef  TYPE_4__ bfd ;
struct TYPE_16__ {TYPE_3__* howto; scalar_t__ address; int /*<<< orphan*/  addend; TYPE_2__** sym_ptr_ptr; } ;
typedef  TYPE_5__ arelent ;
struct TYPE_13__ {TYPE_1__* the_bfd; } ;
struct TYPE_12__ {scalar_t__ xvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_12_PCREL ; 
 int /*<<< orphan*/  BFD_RELOC_14 ; 
 int /*<<< orphan*/  BFD_RELOC_16 ; 
 int /*<<< orphan*/  BFD_RELOC_16_PCREL ; 
 int /*<<< orphan*/  BFD_RELOC_24_PCREL ; 
 int /*<<< orphan*/  BFD_RELOC_26 ; 
 int /*<<< orphan*/  BFD_RELOC_32 ; 
 int /*<<< orphan*/  BFD_RELOC_32_PCREL ; 
 int /*<<< orphan*/  BFD_RELOC_64 ; 
 int /*<<< orphan*/  BFD_RELOC_64_PCREL ; 
 int /*<<< orphan*/  BFD_RELOC_8 ; 
 int /*<<< orphan*/  BFD_RELOC_8_PCREL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 TYPE_3__* bfd_reloc_type_lookup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_elf_validate_reloc (bfd *abfd, arelent *areloc)
{
  /* Check whether we really have an ELF howto.  */

  if ((*areloc->sym_ptr_ptr)->the_bfd->xvec != abfd->xvec)
    {
      bfd_reloc_code_real_type code;
      reloc_howto_type *howto;

      /* Alien reloc: Try to determine its type to replace it with an
	 equivalent ELF reloc.  */

      if (areloc->howto->pc_relative)
	{
	  switch (areloc->howto->bitsize)
	    {
	    case 8:
	      code = BFD_RELOC_8_PCREL;
	      break;
	    case 12:
	      code = BFD_RELOC_12_PCREL;
	      break;
	    case 16:
	      code = BFD_RELOC_16_PCREL;
	      break;
	    case 24:
	      code = BFD_RELOC_24_PCREL;
	      break;
	    case 32:
	      code = BFD_RELOC_32_PCREL;
	      break;
	    case 64:
	      code = BFD_RELOC_64_PCREL;
	      break;
	    default:
	      goto fail;
	    }

	  howto = bfd_reloc_type_lookup (abfd, code);

	  if (areloc->howto->pcrel_offset != howto->pcrel_offset)
	    {
	      if (howto->pcrel_offset)
		areloc->addend += areloc->address;
	      else
		areloc->addend -= areloc->address; /* addend is unsigned!! */
	    }
	}
      else
	{
	  switch (areloc->howto->bitsize)
	    {
	    case 8:
	      code = BFD_RELOC_8;
	      break;
	    case 14:
	      code = BFD_RELOC_14;
	      break;
	    case 16:
	      code = BFD_RELOC_16;
	      break;
	    case 26:
	      code = BFD_RELOC_26;
	      break;
	    case 32:
	      code = BFD_RELOC_32;
	      break;
	    case 64:
	      code = BFD_RELOC_64;
	      break;
	    default:
	      goto fail;
	    }

	  howto = bfd_reloc_type_lookup (abfd, code);
	}

      if (howto)
	areloc->howto = howto;
      else
	goto fail;
    }

  return TRUE;

 fail:
  (*_bfd_error_handler)
    (_("%B: unsupported relocation type %s"),
     abfd, areloc->howto->name);
  bfd_set_error (bfd_error_bad_value);
  return FALSE;
}