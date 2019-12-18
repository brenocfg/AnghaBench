#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_4__* section; } ;
struct TYPE_20__ {TYPE_1__ indirect; } ;
struct bfd_link_order {unsigned int size; TYPE_2__ u; } ;
struct bfd_link_info {int dummy; } ;
typedef  long bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_22__ {long size; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_4__ asection ;
struct TYPE_23__ {unsigned int address; unsigned int addend; TYPE_3__* howto; } ;
typedef  TYPE_5__ arelent ;
struct TYPE_21__ {int type; unsigned int size; } ;

/* Variables and functions */
#define  ABS32 134 
#define  ABS32CODE 133 
#define  ABS32CODE_SHRUNK 132 
#define  ALIGNDONE 131 
 long BAL_MASK ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
#define  CALLJ 130 
 int /*<<< orphan*/  FALSE ; 
#define  PCREL13 129 
 long PCREL13_MASK ; 
#define  PCREL24 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 long bfd_canonicalize_reloc (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * bfd_generic_get_relocated_section_contents (int /*<<< orphan*/ *,struct bfd_link_info*,struct bfd_link_order*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long bfd_get_reloc_upper_bound (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int bfd_get_section_contents (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,long,long) ; 
 TYPE_5__** bfd_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callj_callback (int /*<<< orphan*/ *,struct bfd_link_info*,TYPE_5__*,int /*<<< orphan*/ *,unsigned int,unsigned int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calljx_callback (int /*<<< orphan*/ *,struct bfd_link_info*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_5__**) ; 
 long get_value (TYPE_5__*,struct bfd_link_info*,TYPE_4__*) ; 
 long output_addr (TYPE_4__*) ; 

__attribute__((used)) static bfd_byte *
b_out_bfd_get_relocated_section_contents (bfd *output_bfd,
					  struct bfd_link_info *link_info,
					  struct bfd_link_order *link_order,
					  bfd_byte *data,
					  bfd_boolean relocatable,
					  asymbol **symbols)
{
  /* Get enough memory to hold the stuff.  */
  bfd *input_bfd = link_order->u.indirect.section->owner;
  asection *input_section = link_order->u.indirect.section;
  long reloc_size = bfd_get_reloc_upper_bound (input_bfd, input_section);
  arelent **reloc_vector = NULL;
  long reloc_count;

  if (reloc_size < 0)
    goto error_return;

  /* If producing relocatable output, don't bother to relax.  */
  if (relocatable)
    return bfd_generic_get_relocated_section_contents (output_bfd, link_info,
						       link_order,
						       data, relocatable,
						       symbols);

  reloc_vector = bfd_malloc ((bfd_size_type) reloc_size);
  if (reloc_vector == NULL && reloc_size != 0)
    goto error_return;

  /* Read in the section.  */
  BFD_ASSERT (bfd_get_section_contents (input_bfd,
					input_section,
					data,
					(bfd_vma) 0,
					input_section->size));

  reloc_count = bfd_canonicalize_reloc (input_bfd,
					input_section,
					reloc_vector,
					symbols);
  if (reloc_count < 0)
    goto error_return;
  if (reloc_count > 0)
    {
      arelent **parent = reloc_vector;
      arelent *reloc ;
      unsigned int dst_address = 0;
      unsigned int src_address = 0;
      unsigned int run;
      unsigned int idx;

      /* Find how long a run we can do.  */
      while (dst_address < link_order->size)
	{
	  reloc = *parent;
	  if (reloc)
	    {
	      /* Note that the relaxing didn't tie up the addresses in the
		 relocation, so we use the original address to work out the
		 run of non-relocated data.  */
	      BFD_ASSERT (reloc->address >= src_address);
	      run = reloc->address - src_address;
	      parent++;
	    }
	  else
	    run = link_order->size - dst_address;

	  /* Copy the bytes.  */
	  for (idx = 0; idx < run; idx++)
	    data[dst_address++] = data[src_address++];

	  /* Now do the relocation.  */
	  if (reloc)
	    {
	      switch (reloc->howto->type)
		{
		case ABS32CODE:
		  calljx_callback (input_bfd, link_info, reloc,
				   src_address + data, dst_address + data,
				   input_section);
		  src_address += 4;
		  dst_address += 4;
		  break;
		case ABS32:
		  bfd_put_32 (input_bfd,
			      (bfd_get_32 (input_bfd, data + src_address)
			       + get_value (reloc, link_info, input_section)),
			      data + dst_address);
		  src_address += 4;
		  dst_address += 4;
		  break;
		case CALLJ:
		  callj_callback (input_bfd, link_info, reloc, data,
				  src_address, dst_address, input_section,
				  FALSE);
		  src_address += 4;
		  dst_address += 4;
		  break;
		case ALIGNDONE:
		  BFD_ASSERT (reloc->addend >= src_address);
		  BFD_ASSERT ((bfd_vma) reloc->addend
			      <= input_section->size);
		  src_address = reloc->addend;
		  dst_address = ((dst_address + reloc->howto->size)
				 & ~reloc->howto->size);
		  break;
		case ABS32CODE_SHRUNK:
		  /* This used to be a callx, but we've found out that a
		     callj will reach, so do the right thing.  */
		  callj_callback (input_bfd, link_info, reloc, data,
				  src_address + 4, dst_address, input_section,
				  TRUE);
		  dst_address += 4;
		  src_address += 8;
		  break;
		case PCREL24:
		  {
		    long int word = bfd_get_32 (input_bfd,
						data + src_address);
		    bfd_vma value;

		    value = get_value (reloc, link_info, input_section);
		    word = ((word & ~BAL_MASK)
			    | (((word & BAL_MASK)
				+ value
				- output_addr (input_section)
				+ reloc->addend)
			       & BAL_MASK));

		    bfd_put_32 (input_bfd, (bfd_vma) word, data + dst_address);
		    dst_address += 4;
		    src_address += 4;

		  }
		  break;
		case PCREL13:
		  {
		    long int word = bfd_get_32 (input_bfd,
						data + src_address);
		    bfd_vma value;

		    value = get_value (reloc, link_info, input_section);
		    word = ((word & ~PCREL13_MASK)
			    | (((word & PCREL13_MASK)
				+ value
				+ reloc->addend
				- output_addr (input_section))
			       & PCREL13_MASK));

		    bfd_put_32 (input_bfd, (bfd_vma) word, data + dst_address);
		    dst_address += 4;
		    src_address += 4;
		  }
		  break;

		default:
		  abort ();
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