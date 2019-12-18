#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comp_unit {int /*<<< orphan*/  abbrevs; int /*<<< orphan*/ * info_ptr_unit; int /*<<< orphan*/ * abfd; } ;
struct TYPE_2__ {char* str; int val; } ;
struct attribute {int name; TYPE_1__ u; } ;
struct abbrev_info {unsigned int num_attrs; int /*<<< orphan*/ * attrs; } ;
typedef  int bfd_uint64_t ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
#define  DW_AT_MIPS_linkage_name 130 
#define  DW_AT_name 129 
#define  DW_AT_specification 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 struct abbrev_info* lookup_abbrev (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_attribute (struct attribute*,int /*<<< orphan*/ *,struct comp_unit*,int /*<<< orphan*/ *) ; 
 unsigned int read_unsigned_leb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static char *
find_abstract_instance_name (struct comp_unit *unit, bfd_uint64_t die_ref)
{
  bfd *abfd = unit->abfd;
  bfd_byte *info_ptr;
  unsigned int abbrev_number, bytes_read, i;
  struct abbrev_info *abbrev;
  struct attribute attr;
  char *name = 0;

  info_ptr = unit->info_ptr_unit + die_ref;
  abbrev_number = read_unsigned_leb128 (abfd, info_ptr, &bytes_read);
  info_ptr += bytes_read;

  if (abbrev_number)
    {
      abbrev = lookup_abbrev (abbrev_number, unit->abbrevs);
      if (! abbrev)
	{
	  (*_bfd_error_handler) (_("Dwarf Error: Could not find abbrev number %u."),
				 abbrev_number);
	  bfd_set_error (bfd_error_bad_value);
	}
      else
	{
	  for (i = 0; i < abbrev->num_attrs; ++i)
	    {
	      info_ptr = read_attribute (&attr, &abbrev->attrs[i], unit, info_ptr);
	      switch (attr.name)
		{
		case DW_AT_name:
		  /* Prefer DW_AT_MIPS_linkage_name over DW_AT_name.  */
		  if (name == NULL)
		    name = attr.u.str;
		  break;
		case DW_AT_specification:
		  name = find_abstract_instance_name (unit, attr.u.val);
		  break;
		case DW_AT_MIPS_linkage_name:
		  name = attr.u.str;
		  break;
		default:
		  break;
		}
	    }
	}
    }
  return (name);
}