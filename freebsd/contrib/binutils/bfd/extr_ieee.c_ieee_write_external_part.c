#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  external_part; } ;
struct TYPE_24__ {TYPE_2__ r; } ;
struct TYPE_25__ {TYPE_3__ w; } ;
typedef  TYPE_4__ ieee_data_type ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  unsigned int bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_26__ {int flags; TYPE_6__** outsymbols; } ;
typedef  TYPE_5__ bfd ;
struct TYPE_27__ {unsigned int value; int flags; TYPE_14__* section; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ asymbol ;
struct TYPE_22__ {unsigned int vma; int /*<<< orphan*/  symbol; } ;
struct TYPE_21__ {int /*<<< orphan*/  symbol; } ;
struct TYPE_20__ {unsigned int output_offset; TYPE_1__* output_section; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int EXEC_P ; 
 scalar_t__ FALSE ; 
 TYPE_4__* IEEE_DATA (TYPE_5__*) ; 
 int IEEE_PUBLIC_BASE ; 
 unsigned int IEEE_REFERENCE_BASE ; 
 scalar_t__ TRUE ; 
 TYPE_17__* bfd_abs_section_ptr ; 
 int /*<<< orphan*/  bfd_is_abs_section (TYPE_14__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_14__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_14__*) ; 
 int /*<<< orphan*/  bfd_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  ieee_attribute_record_enum ; 
 int ieee_external_reference_enum ; 
 int ieee_external_symbol_enum ; 
 int /*<<< orphan*/  ieee_value_record_enum ; 
 int ieee_weak_external_reference_enum ; 
 int /*<<< orphan*/  ieee_write_2bytes (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_byte (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ieee_write_expression (TYPE_5__*,unsigned int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_id (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_int (TYPE_5__*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_write_external_part (bfd *abfd)
{
  asymbol **q;
  ieee_data_type *ieee = IEEE_DATA (abfd);
  unsigned int reference_index = IEEE_REFERENCE_BASE;
  unsigned int public_index = IEEE_PUBLIC_BASE + 2;
  file_ptr here = bfd_tell (abfd);
  bfd_boolean hadone = FALSE;

  if (abfd->outsymbols != (asymbol **) NULL)
    {

      for (q = abfd->outsymbols; *q != (asymbol *) NULL; q++)
	{
	  asymbol *p = *q;

	  if (bfd_is_und_section (p->section))
	    {
	      /* This must be a symbol reference.  */
	      if (! ieee_write_byte (abfd, ieee_external_reference_enum)
		  || ! ieee_write_int (abfd, (bfd_vma) reference_index)
		  || ! ieee_write_id (abfd, p->name))
		return FALSE;
	      p->value = reference_index;
	      reference_index++;
	      hadone = TRUE;
	    }
	  else if (bfd_is_com_section (p->section))
	    {
	      /* This is a weak reference.  */
	      if (! ieee_write_byte (abfd, ieee_external_reference_enum)
		  || ! ieee_write_int (abfd, (bfd_vma) reference_index)
		  || ! ieee_write_id (abfd, p->name)
		  || ! ieee_write_byte (abfd,
					ieee_weak_external_reference_enum)
		  || ! ieee_write_int (abfd, (bfd_vma) reference_index)
		  || ! ieee_write_int (abfd, p->value))
		return FALSE;
	      p->value = reference_index;
	      reference_index++;
	      hadone = TRUE;
	    }
	  else if (p->flags & BSF_GLOBAL)
	    {
	      /* This must be a symbol definition.  */
	      if (! ieee_write_byte (abfd, ieee_external_symbol_enum)
		  || ! ieee_write_int (abfd, (bfd_vma) public_index)
		  || ! ieee_write_id (abfd, p->name)
		  || ! ieee_write_2bytes (abfd, ieee_attribute_record_enum)
		  || ! ieee_write_int (abfd, (bfd_vma) public_index)
		  || ! ieee_write_byte (abfd, 15) /* Instruction address.  */
		  || ! ieee_write_byte (abfd, 19) /* Static symbol.  */
		  || ! ieee_write_byte (abfd, 1)) /* One of them.  */
		return FALSE;

	      /* Write out the value.  */
	      if (! ieee_write_2bytes (abfd, ieee_value_record_enum)
		  || ! ieee_write_int (abfd, (bfd_vma) public_index))
		return FALSE;
	      if (! bfd_is_abs_section (p->section))
		{
		  if (abfd->flags & EXEC_P)
		    {
		      /* If fully linked, then output all symbols
			 relocated.  */
		      if (! (ieee_write_int
			     (abfd,
			      (p->value
			       + p->section->output_offset
			       + p->section->output_section->vma))))
			return FALSE;
		    }
		  else
		    {
		      if (! (ieee_write_expression
			     (abfd,
			      p->value + p->section->output_offset,
			      p->section->output_section->symbol,
			      FALSE, 0)))
			return FALSE;
		    }
		}
	      else
		{
		  if (! ieee_write_expression (abfd,
					       p->value,
					       bfd_abs_section_ptr->symbol,
					       FALSE, 0))
		    return FALSE;
		}
	      p->value = public_index;
	      public_index++;
	      hadone = TRUE;
	    }
	  else
	    {
	      /* This can happen - when there are gaps in the symbols read
	         from an input ieee file.  */
	    }
	}
    }
  if (hadone)
    ieee->w.r.external_part = here;

  return TRUE;
}