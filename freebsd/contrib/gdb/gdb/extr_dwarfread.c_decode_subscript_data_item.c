#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
#define  FMT_ET 136 
#define  FMT_FT_C_C 135 
#define  FMT_FT_C_X 134 
#define  FMT_FT_X_C 133 
#define  FMT_FT_X_X 132 
#define  FMT_UT_C_C 131 
#define  FMT_UT_C_X 130 
#define  FMT_UT_X_C 129 
#define  FMT_UT_X_X 128 
 int /*<<< orphan*/  FT_INTEGER ; 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 int SIZEOF_FMT_FT ; 
 int SIZEOF_FORMAT_SPECIFIER ; 
 int TARGET_FT_LONG_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct type* create_array_type (struct type*,struct type*,struct type*) ; 
 struct type* create_range_type (struct type*,struct type*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  current_objfile ; 
 struct type* decode_array_element_type (char*) ; 
 struct type* decode_fund_type (unsigned short) ; 
 struct type* dwarf_fundamental_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 void* target_to_host (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
decode_subscript_data_item (char *scan, char *end)
{
  struct type *typep = NULL;	/* Array type we are building */
  struct type *nexttype;	/* Type of each element (may be array) */
  struct type *indextype;	/* Type of this index */
  struct type *rangetype;
  unsigned int format;
  unsigned short fundtype;
  unsigned long lowbound;
  unsigned long highbound;
  int nbytes;

  format = target_to_host (scan, SIZEOF_FORMAT_SPECIFIER, GET_UNSIGNED,
			   current_objfile);
  scan += SIZEOF_FORMAT_SPECIFIER;
  switch (format)
    {
    case FMT_ET:
      typep = decode_array_element_type (scan);
      break;
    case FMT_FT_C_C:
      fundtype = target_to_host (scan, SIZEOF_FMT_FT, GET_UNSIGNED,
				 current_objfile);
      indextype = decode_fund_type (fundtype);
      scan += SIZEOF_FMT_FT;
      nbytes = TARGET_FT_LONG_SIZE (current_objfile);
      lowbound = target_to_host (scan, nbytes, GET_UNSIGNED, current_objfile);
      scan += nbytes;
      highbound = target_to_host (scan, nbytes, GET_UNSIGNED, current_objfile);
      scan += nbytes;
      nexttype = decode_subscript_data_item (scan, end);
      if (nexttype == NULL)
	{
	  /* Munged subscript data or other problem, fake it. */
	  complaint (&symfile_complaints,
		     "DIE @ 0x%x \"%s\", can't decode subscript data items",
		     DIE_ID, DIE_NAME);
	  nexttype = dwarf_fundamental_type (current_objfile, FT_INTEGER);
	}
      rangetype = create_range_type ((struct type *) NULL, indextype,
				     lowbound, highbound);
      typep = create_array_type ((struct type *) NULL, nexttype, rangetype);
      break;
    case FMT_FT_C_X:
    case FMT_FT_X_C:
    case FMT_FT_X_X:
    case FMT_UT_C_C:
    case FMT_UT_C_X:
    case FMT_UT_X_C:
    case FMT_UT_X_X:
      complaint (&symfile_complaints,
		 "DIE @ 0x%x \"%s\", array subscript format 0x%x not handled yet",
		 DIE_ID, DIE_NAME, format);
      nexttype = dwarf_fundamental_type (current_objfile, FT_INTEGER);
      rangetype = create_range_type ((struct type *) NULL, nexttype, 0, 0);
      typep = create_array_type ((struct type *) NULL, nexttype, rangetype);
      break;
    default:
      complaint (&symfile_complaints,
		 "DIE @ 0x%x \"%s\", unknown array subscript format %x", DIE_ID,
		 DIE_NAME, format);
      nexttype = dwarf_fundamental_type (current_objfile, FT_INTEGER);
      rangetype = create_range_type ((struct type *) NULL, nexttype, 0, 0);
      typep = create_array_type ((struct type *) NULL, nexttype, rangetype);
      break;
    }
  return (typep);
}