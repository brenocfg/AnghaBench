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
typedef  void* DIE_REF ;

/* Variables and functions */
#define  AT_fund_type 131 
#define  AT_mod_fund_type 130 
#define  AT_mod_u_d_type 129 
#define  AT_user_def_type 128 
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  FT_INTEGER ; 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 int SIZEOF_ATTRIBUTE ; 
 struct type* alloc_utype (void*,int /*<<< orphan*/ *) ; 
 int attribute_size (unsigned short) ; 
 int /*<<< orphan*/  bad_array_element_type_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  current_objfile ; 
 struct type* decode_fund_type (unsigned short) ; 
 struct type* decode_mod_fund_type (char*) ; 
 struct type* decode_mod_u_d_type (char*) ; 
 struct type* dwarf_fundamental_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* lookup_utype (void*) ; 
 void* target_to_host (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
decode_array_element_type (char *scan)
{
  struct type *typep;
  DIE_REF die_ref;
  unsigned short attribute;
  unsigned short fundtype;
  int nbytes;

  attribute = target_to_host (scan, SIZEOF_ATTRIBUTE, GET_UNSIGNED,
			      current_objfile);
  scan += SIZEOF_ATTRIBUTE;
  nbytes = attribute_size (attribute);
  if (nbytes == -1)
    {
      bad_array_element_type_complaint (DIE_ID, DIE_NAME, attribute);
      typep = dwarf_fundamental_type (current_objfile, FT_INTEGER);
    }
  else
    {
      switch (attribute)
	{
	case AT_fund_type:
	  fundtype = target_to_host (scan, nbytes, GET_UNSIGNED,
				     current_objfile);
	  typep = decode_fund_type (fundtype);
	  break;
	case AT_mod_fund_type:
	  typep = decode_mod_fund_type (scan);
	  break;
	case AT_user_def_type:
	  die_ref = target_to_host (scan, nbytes, GET_UNSIGNED,
				    current_objfile);
	  typep = lookup_utype (die_ref);
	  if (typep == NULL)
	    {
	      typep = alloc_utype (die_ref, NULL);
	    }
	  break;
	case AT_mod_u_d_type:
	  typep = decode_mod_u_d_type (scan);
	  break;
	default:
	  bad_array_element_type_complaint (DIE_ID, DIE_NAME, attribute);
	  typep = dwarf_fundamental_type (current_objfile, FT_INTEGER);
	  break;
	}
    }
  return (typep);
}