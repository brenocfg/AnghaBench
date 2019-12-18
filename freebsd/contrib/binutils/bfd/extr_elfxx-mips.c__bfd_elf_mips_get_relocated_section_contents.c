#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_11__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
struct TYPE_37__ {TYPE_10__* section; } ;
struct TYPE_38__ {TYPE_1__ indirect; } ;
struct bfd_link_order {TYPE_2__ u; } ;
struct bfd_link_info {TYPE_7__* callbacks; TYPE_3__* hash; } ;
struct TYPE_41__ {struct bfd_link_hash_entry* link; } ;
struct TYPE_40__ {int value; } ;
struct TYPE_42__ {TYPE_5__ i; TYPE_4__ def; } ;
struct bfd_link_hash_entry {int type; TYPE_6__ u; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_45__ {scalar_t__ xvec; } ;
typedef  TYPE_9__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_35__ {size_t reloc_count; TYPE_11__** orelocation; struct TYPE_35__* output_section; scalar_t__ size; scalar_t__ rawsize; TYPE_9__* owner; } ;
typedef  TYPE_10__ asection ;
struct TYPE_36__ {int /*<<< orphan*/  address; int /*<<< orphan*/  addend; TYPE_8__* howto; int /*<<< orphan*/ ** sym_ptr_ptr; } ;
typedef  TYPE_11__ arelent ;
struct TYPE_44__ {scalar_t__ special_function; int /*<<< orphan*/  name; } ;
struct TYPE_43__ {int /*<<< orphan*/  (* reloc_overflow ) (struct bfd_link_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reloc_dangerous ) (struct bfd_link_info*,char*,TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* undefined_symbol ) (struct bfd_link_info*,int /*<<< orphan*/ ,TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_39__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _bfd_mips_elf32_gprel16_reloc ; 
 int _bfd_mips_elf_gprel16_with_gp (TYPE_9__*,int /*<<< orphan*/ *,TYPE_11__*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 long bfd_canonicalize_reloc (TYPE_9__*,TYPE_10__*,TYPE_11__**,int /*<<< orphan*/ **) ; 
 long bfd_get_reloc_upper_bound (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct bfd_hash_entry* bfd_hash_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  bfd_link_hash_common 139 
#define  bfd_link_hash_defined 138 
#define  bfd_link_hash_defweak 137 
#define  bfd_link_hash_indirect 136 
#define  bfd_link_hash_new 135 
#define  bfd_link_hash_undefined 134 
#define  bfd_link_hash_undefweak 133 
#define  bfd_link_hash_warning 132 
 TYPE_11__** bfd_malloc (long) ; 
 int bfd_perform_relocation (TYPE_9__*,TYPE_11__*,int /*<<< orphan*/ *,TYPE_10__*,TYPE_9__*,char**) ; 
#define  bfd_reloc_dangerous 131 
 int bfd_reloc_ok ; 
#define  bfd_reloc_outofrange 130 
#define  bfd_reloc_overflow 129 
#define  bfd_reloc_undefined 128 
 int /*<<< orphan*/  free (TYPE_11__**) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,int /*<<< orphan*/ ,TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bfd_link_info*,char*,TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct bfd_link_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ; 

bfd_byte *
_bfd_elf_mips_get_relocated_section_contents
  (bfd *abfd,
   struct bfd_link_info *link_info,
   struct bfd_link_order *link_order,
   bfd_byte *data,
   bfd_boolean relocatable,
   asymbol **symbols)
{
  /* Get enough memory to hold the stuff */
  bfd *input_bfd = link_order->u.indirect.section->owner;
  asection *input_section = link_order->u.indirect.section;
  bfd_size_type sz;

  long reloc_size = bfd_get_reloc_upper_bound (input_bfd, input_section);
  arelent **reloc_vector = NULL;
  long reloc_count;

  if (reloc_size < 0)
    goto error_return;

  reloc_vector = bfd_malloc (reloc_size);
  if (reloc_vector == NULL && reloc_size != 0)
    goto error_return;

  /* read in the section */
  sz = input_section->rawsize ? input_section->rawsize : input_section->size;
  if (!bfd_get_section_contents (input_bfd, input_section, data, 0, sz))
    goto error_return;

  reloc_count = bfd_canonicalize_reloc (input_bfd,
					input_section,
					reloc_vector,
					symbols);
  if (reloc_count < 0)
    goto error_return;

  if (reloc_count > 0)
    {
      arelent **parent;
      /* for mips */
      int gp_found;
      bfd_vma gp = 0x12345678;	/* initialize just to shut gcc up */

      {
	struct bfd_hash_entry *h;
	struct bfd_link_hash_entry *lh;
	/* Skip all this stuff if we aren't mixing formats.  */
	if (abfd && input_bfd
	    && abfd->xvec == input_bfd->xvec)
	  lh = 0;
	else
	  {
	    h = bfd_hash_lookup (&link_info->hash->table, "_gp", FALSE, FALSE);
	    lh = (struct bfd_link_hash_entry *) h;
	  }
      lookup:
	if (lh)
	  {
	    switch (lh->type)
	      {
	      case bfd_link_hash_undefined:
	      case bfd_link_hash_undefweak:
	      case bfd_link_hash_common:
		gp_found = 0;
		break;
	      case bfd_link_hash_defined:
	      case bfd_link_hash_defweak:
		gp_found = 1;
		gp = lh->u.def.value;
		break;
	      case bfd_link_hash_indirect:
	      case bfd_link_hash_warning:
		lh = lh->u.i.link;
		/* @@FIXME  ignoring warning for now */
		goto lookup;
	      case bfd_link_hash_new:
	      default:
		abort ();
	      }
	  }
	else
	  gp_found = 0;
      }
      /* end mips */
      for (parent = reloc_vector; *parent != NULL; parent++)
	{
	  char *error_message = NULL;
	  bfd_reloc_status_type r;

	  /* Specific to MIPS: Deal with relocation types that require
	     knowing the gp of the output bfd.  */
	  asymbol *sym = *(*parent)->sym_ptr_ptr;

	  /* If we've managed to find the gp and have a special
	     function for the relocation then go ahead, else default
	     to the generic handling.  */
	  if (gp_found
	      && (*parent)->howto->special_function
	      == _bfd_mips_elf32_gprel16_reloc)
	    r = _bfd_mips_elf_gprel16_with_gp (input_bfd, sym, *parent,
					       input_section, relocatable,
					       data, gp);
	  else
	    r = bfd_perform_relocation (input_bfd, *parent, data,
					input_section,
					relocatable ? abfd : NULL,
					&error_message);

	  if (relocatable)
	    {
	      asection *os = input_section->output_section;

	      /* A partial link, so keep the relocs */
	      os->orelocation[os->reloc_count] = *parent;
	      os->reloc_count++;
	    }

	  if (r != bfd_reloc_ok)
	    {
	      switch (r)
		{
		case bfd_reloc_undefined:
		  if (!((*link_info->callbacks->undefined_symbol)
			(link_info, bfd_asymbol_name (*(*parent)->sym_ptr_ptr),
			 input_bfd, input_section, (*parent)->address, TRUE)))
		    goto error_return;
		  break;
		case bfd_reloc_dangerous:
		  BFD_ASSERT (error_message != NULL);
		  if (!((*link_info->callbacks->reloc_dangerous)
			(link_info, error_message, input_bfd, input_section,
			 (*parent)->address)))
		    goto error_return;
		  break;
		case bfd_reloc_overflow:
		  if (!((*link_info->callbacks->reloc_overflow)
			(link_info, NULL,
			 bfd_asymbol_name (*(*parent)->sym_ptr_ptr),
			 (*parent)->howto->name, (*parent)->addend,
			 input_bfd, input_section, (*parent)->address)))
		    goto error_return;
		  break;
		case bfd_reloc_outofrange:
		default:
		  abort ();
		  break;
		}

	    }
	}
    }
  if (reloc_vector != NULL)
    free (reloc_vector);
  return data;

error_return:
  if (reloc_vector != NULL)
    free (reloc_vector);
  return NULL;
}