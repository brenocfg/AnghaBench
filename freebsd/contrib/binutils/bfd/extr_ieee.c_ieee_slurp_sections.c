#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ieee_record_enum_type ;
struct TYPE_9__ {scalar_t__ section_part; } ;
struct TYPE_10__ {TYPE_1__ r; } ;
struct TYPE_11__ {unsigned int section_count; int /*<<< orphan*/  h; TYPE_4__** section_table; TYPE_2__ w; } ;
typedef  TYPE_3__ ieee_data_type ;
typedef  scalar_t__ file_ptr ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {int flags; char* name; size_t size; size_t vma; size_t lma; int /*<<< orphan*/  alignment_power; } ;
typedef  TYPE_4__ asection ;

/* Variables and functions */
 TYPE_3__* IEEE_DATA (int /*<<< orphan*/ *) ; 
 void* SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_DATA ; 
 int SEC_ROM ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bfd_log2 (size_t) ; 
 TYPE_4__* get_section_entry (int /*<<< orphan*/ *,TYPE_3__*,unsigned int) ; 
#define  ieee_e2_first_byte_enum 137 
#define  ieee_m_value_enum 136 
#define  ieee_mau_size_enum 135 
#define  ieee_physical_region_size_enum 134 
#define  ieee_region_base_address_enum 133 
#define  ieee_section_alignment_enum 132 
#define  ieee_section_base_address_enum 131 
#define  ieee_section_offset_enum 130 
#define  ieee_section_size_enum 129 
#define  ieee_section_type_enum 128 
 int /*<<< orphan*/  ieee_seek (TYPE_3__*,scalar_t__) ; 
 size_t must_parse_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_2bytes (int /*<<< orphan*/ *) ; 
 char* read_id (int /*<<< orphan*/ *) ; 
 int this_byte (int /*<<< orphan*/ *) ; 
 int this_byte_and_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ieee_slurp_sections (bfd *abfd)
{
  ieee_data_type *ieee = IEEE_DATA (abfd);
  file_ptr offset = ieee->w.r.section_part;
  char *name;

  if (offset != 0)
    {
      bfd_byte section_type[3];

      ieee_seek (ieee, offset);
      while (TRUE)
	{
	  switch (this_byte (&(ieee->h)))
	    {
	    case ieee_section_type_enum:
	      {
		asection *section;
		unsigned int section_index;

		next_byte (&(ieee->h));
		section_index = must_parse_int (&(ieee->h));

		section = get_section_entry (abfd, ieee, section_index);

		section_type[0] = this_byte_and_next (&(ieee->h));

		/* Set minimal section attributes. Attributes are
		   extended later, based on section contents.  */
		switch (section_type[0])
		  {
		  case 0xC1:
		    /* Normal attributes for absolute sections.  */
		    section_type[1] = this_byte (&(ieee->h));
		    section->flags = SEC_ALLOC;
		    switch (section_type[1])
		      {
			/* AS Absolute section attributes.  */
		      case 0xD3:
			next_byte (&(ieee->h));
			section_type[2] = this_byte (&(ieee->h));
			switch (section_type[2])
			  {
			  case 0xD0:
			    /* Normal code.  */
			    next_byte (&(ieee->h));
			    section->flags |= SEC_CODE;
			    break;
			  case 0xC4:
			    /* Normal data.  */
			    next_byte (&(ieee->h));
			    section->flags |= SEC_DATA;
			    break;
			  case 0xD2:
			    next_byte (&(ieee->h));
			    /* Normal rom data.  */
			    section->flags |= SEC_ROM | SEC_DATA;
			    break;
			  default:
			    break;
			  }
		      }
		    break;

		    /* Named relocatable sections (type C).  */
		  case 0xC3:
		    section_type[1] = this_byte (&(ieee->h));
		    section->flags = SEC_ALLOC;
		    switch (section_type[1])
		      {
		      case 0xD0:	/* Normal code (CP).  */
			next_byte (&(ieee->h));
			section->flags |= SEC_CODE;
			break;
		      case 0xC4:	/* Normal data (CD).  */
			next_byte (&(ieee->h));
			section->flags |= SEC_DATA;
			break;
		      case 0xD2:	/* Normal rom data (CR).  */
			next_byte (&(ieee->h));
			section->flags |= SEC_ROM | SEC_DATA;
			break;
		      default:
			break;
		      }
		  }

		/* Read section name, use it if non empty.  */
		name = read_id (&ieee->h);
		if (name[0])
		  section->name = name;

		/* Skip these fields, which we don't care about.  */
		{
		  bfd_vma parent, brother, context;

		  parse_int (&(ieee->h), &parent);
		  parse_int (&(ieee->h), &brother);
		  parse_int (&(ieee->h), &context);
		}
	      }
	      break;
	    case ieee_section_alignment_enum:
	      {
		unsigned int section_index;
		bfd_vma value;
		asection *section;

		next_byte (&(ieee->h));
		section_index = must_parse_int (&ieee->h);
		section = get_section_entry (abfd, ieee, section_index);
		if (section_index > ieee->section_count)
		  ieee->section_count = section_index;

		section->alignment_power =
		  bfd_log2 (must_parse_int (&ieee->h));
		(void) parse_int (&(ieee->h), &value);
	      }
	      break;
	    case ieee_e2_first_byte_enum:
	      {
		asection *section;
		ieee_record_enum_type t;

		t = (ieee_record_enum_type) (read_2bytes (&(ieee->h)));
		switch (t)
		  {
		  case ieee_section_size_enum:
		    section = ieee->section_table[must_parse_int (&(ieee->h))];
		    section->size = must_parse_int (&(ieee->h));
		    break;
		  case ieee_physical_region_size_enum:
		    section = ieee->section_table[must_parse_int (&(ieee->h))];
		    section->size = must_parse_int (&(ieee->h));
		    break;
		  case ieee_region_base_address_enum:
		    section = ieee->section_table[must_parse_int (&(ieee->h))];
		    section->vma = must_parse_int (&(ieee->h));
		    section->lma = section->vma;
		    break;
		  case ieee_mau_size_enum:
		    must_parse_int (&(ieee->h));
		    must_parse_int (&(ieee->h));
		    break;
		  case ieee_m_value_enum:
		    must_parse_int (&(ieee->h));
		    must_parse_int (&(ieee->h));
		    break;
		  case ieee_section_base_address_enum:
		    section = ieee->section_table[must_parse_int (&(ieee->h))];
		    section->vma = must_parse_int (&(ieee->h));
		    section->lma = section->vma;
		    break;
		  case ieee_section_offset_enum:
		    (void) must_parse_int (&(ieee->h));
		    (void) must_parse_int (&(ieee->h));
		    break;
		  default:
		    return;
		  }
	      }
	      break;
	    default:
	      return;
	    }
	}
    }
}