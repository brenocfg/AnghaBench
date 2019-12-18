#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_22__ {int flags; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_23__ {unsigned int reloc_count; scalar_t__ lma; scalar_t__ size; scalar_t__ index; int /*<<< orphan*/ * symbol; TYPE_3__** orelocation; } ;
typedef  TYPE_2__ asection ;
struct TYPE_24__ {scalar_t__ address; scalar_t__ addend; TYPE_17__* howto; int /*<<< orphan*/ ** sym_ptr_ptr; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_25__ {int /*<<< orphan*/ * data; } ;
struct TYPE_21__ {int size; scalar_t__ pc_relative; int /*<<< orphan*/  pcrel_offset; int /*<<< orphan*/  src_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_FAIL () ; 
 int EXEC_P ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IEEE_SECTION_NUMBER_BASE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int bfd_arch_bits_per_address (TYPE_1__*) ; 
 unsigned int bfd_arch_bits_per_byte (TYPE_1__*) ; 
 scalar_t__ bfd_bwrite (void*,scalar_t__,TYPE_1__*) ; 
 unsigned int bfd_get_reloc_size (TYPE_17__*) ; 
 int /*<<< orphan*/  bfd_get_signed_16 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_32 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_8 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_zalloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  ieee_function_either_close_b_enum ; 
 int /*<<< orphan*/  ieee_function_either_open_b_enum ; 
 int /*<<< orphan*/  ieee_load_constant_bytes_enum ; 
 int /*<<< orphan*/  ieee_load_with_relocation_enum ; 
 TYPE_9__* ieee_per_section (TYPE_2__*) ; 
 int /*<<< orphan*/  ieee_set_current_pc_enum ; 
 int /*<<< orphan*/  ieee_set_current_section_enum ; 
 int /*<<< orphan*/  ieee_write_2bytes (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_expression (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  ieee_write_int (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  qsort (TYPE_3__**,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
do_with_relocs (bfd *abfd, asection *s)
{
  unsigned int number_of_maus_in_address =
    bfd_arch_bits_per_address (abfd) / bfd_arch_bits_per_byte (abfd);
  unsigned int relocs_to_go = s->reloc_count;
  bfd_byte *stream = ieee_per_section (s)->data;
  arelent **p = s->orelocation;
  bfd_size_type current_byte_index = 0;

  qsort (s->orelocation,
	 relocs_to_go,
	 sizeof (arelent **),
	 comp);

  /* Output the section preheader.  */
  if (! ieee_write_byte (abfd, ieee_set_current_section_enum)
      || ! ieee_write_byte (abfd,
			    (bfd_byte) (s->index + IEEE_SECTION_NUMBER_BASE))
      || ! ieee_write_2bytes (abfd, ieee_set_current_pc_enum)
      || ! ieee_write_byte (abfd,
			    (bfd_byte) (s->index + IEEE_SECTION_NUMBER_BASE)))
    return FALSE;

  if ((abfd->flags & EXEC_P) != 0 && relocs_to_go == 0)
    {
      if (! ieee_write_int (abfd, s->lma))
	return FALSE;
    }
  else
    {
      if (! ieee_write_expression (abfd, (bfd_vma) 0, s->symbol, 0, 0))
	return FALSE;
    }

  if (relocs_to_go == 0)
    {
      /* If there aren't any relocations then output the load constant
	 byte opcode rather than the load with relocation opcode.  */
      while (current_byte_index < s->size)
	{
	  bfd_size_type run;
	  unsigned int MAXRUN = 127;

	  run = MAXRUN;
	  if (run > s->size - current_byte_index)
	    run = s->size - current_byte_index;

	  if (run != 0)
	    {
	      if (! ieee_write_byte (abfd, ieee_load_constant_bytes_enum))
		return FALSE;
	      /* Output a stream of bytes.  */
	      if (! ieee_write_int (abfd, run))
		return FALSE;
	      if (bfd_bwrite ((void *) (stream + current_byte_index), run, abfd)
		  != run)
		return FALSE;
	      current_byte_index += run;
	    }
	}
    }
  else
    {
      if (! ieee_write_byte (abfd, ieee_load_with_relocation_enum))
	return FALSE;

      /* Output the data stream as the longest sequence of bytes
	 possible, allowing for the a reasonable packet size and
	 relocation stuffs.  */
      if (stream == NULL)
	{
	  /* Outputting a section without data, fill it up.  */
	  stream = bfd_zalloc (abfd, s->size);
	  if (!stream)
	    return FALSE;
	}
      while (current_byte_index < s->size)
	{
	  bfd_size_type run;
	  unsigned int MAXRUN = 127;

	  if (relocs_to_go)
	    {
	      run = (*p)->address - current_byte_index;
	      if (run > MAXRUN)
		run = MAXRUN;
	    }
	  else
	    run = MAXRUN;

	  if (run > s->size - current_byte_index)
	    run = s->size - current_byte_index;

	  if (run != 0)
	    {
	      /* Output a stream of bytes.  */
	      if (! ieee_write_int (abfd, run))
		return FALSE;
	      if (bfd_bwrite ((void *) (stream + current_byte_index), run, abfd)
		  != run)
		return FALSE;
	      current_byte_index += run;
	    }

	  /* Output any relocations here.  */
	  if (relocs_to_go && (*p) && (*p)->address == current_byte_index)
	    {
	      while (relocs_to_go
		     && (*p) && (*p)->address == current_byte_index)
		{
		  arelent *r = *p;
		  bfd_signed_vma ov;
		  switch (r->howto->size)
		    {
		    case 2:
		      ov = bfd_get_signed_32 (abfd,
					      stream + current_byte_index);
		      current_byte_index += 4;
		      break;
		    case 1:
		      ov = bfd_get_signed_16 (abfd,
					      stream + current_byte_index);
		      current_byte_index += 2;
		      break;
		    case 0:
		      ov = bfd_get_signed_8 (abfd,
					     stream + current_byte_index);
		      current_byte_index++;
		      break;
		    default:
		      ov = 0;
		      BFD_FAIL ();
		      return FALSE;
		    }

		  ov &= r->howto->src_mask;

		  if (r->howto->pc_relative
		      && ! r->howto->pcrel_offset)
		    ov += r->address;

		  if (! ieee_write_byte (abfd,
					 ieee_function_either_open_b_enum))
		    return FALSE;

		  if (r->sym_ptr_ptr != (asymbol **) NULL)
		    {
		      if (! ieee_write_expression (abfd, r->addend + ov,
						   *(r->sym_ptr_ptr),
						   r->howto->pc_relative,
						   (unsigned) s->index))
			return FALSE;
		    }
		  else
		    {
		      if (! ieee_write_expression (abfd, r->addend + ov,
						   (asymbol *) NULL,
						   r->howto->pc_relative,
						   (unsigned) s->index))
			return FALSE;
		    }

		  if (number_of_maus_in_address
		      != bfd_get_reloc_size (r->howto))
		    {
		      bfd_vma rsize = bfd_get_reloc_size (r->howto);
		      if (! ieee_write_int (abfd, rsize))
			return FALSE;
		    }
		  if (! ieee_write_byte (abfd,
					 ieee_function_either_close_b_enum))
		    return FALSE;

		  relocs_to_go--;
		  p++;
		}

	    }
	}
    }

  return TRUE;
}