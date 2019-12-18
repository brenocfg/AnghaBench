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
struct objfile {int dummy; } ;
struct dieinfo {char* die; int die_length; int at_fund_type; int at_ordering; int at_bit_offset; int at_sibling; int at_stmt_list; int has_at_stmt_list; int at_low_pc; int has_at_low_pc; int at_high_pc; int at_language; int at_user_def_type; int at_byte_size; int has_at_byte_size; int at_bit_size; int at_member; int at_discr; char* at_location; char* at_mod_fund_type; char* at_subscr_data; char* at_mod_u_d_type; char* at_element_list; int short_element_list; char* at_discr_value; char* at_string_length; char* at_name; char* at_comp_dir; char* at_producer; int at_start_scope; int at_stride_size; int at_src_info; char* at_prototyped; } ;

/* Variables and functions */
#define  AT_bit_offset 163 
#define  AT_bit_size 162 
#define  AT_byte_size 161 
#define  AT_comp_dir 160 
#define  AT_discr 159 
#define  AT_discr_value 158 
#define  AT_element_list 157 
#define  AT_fund_type 156 
#define  AT_high_pc 155 
#define  AT_language 154 
#define  AT_location 153 
#define  AT_low_pc 152 
#define  AT_member 151 
#define  AT_mod_fund_type 150 
#define  AT_mod_u_d_type 149 
#define  AT_name 148 
#define  AT_ordering 147 
#define  AT_producer 146 
#define  AT_prototyped 145 
#define  AT_short_element_list 144 
#define  AT_sibling 143 
#define  AT_src_info 142 
#define  AT_start_scope 141 
#define  AT_stmt_list 140 
#define  AT_stride_size 139 
#define  AT_string_length 138 
#define  AT_subscr_data 137 
#define  AT_user_def_type 136 
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
#define  FORM_ADDR 135 
#define  FORM_BLOCK2 134 
#define  FORM_BLOCK4 133 
#define  FORM_DATA2 132 
#define  FORM_DATA4 131 
#define  FORM_DATA8 130 
 unsigned short FORM_FROM_ATTR (unsigned short) ; 
#define  FORM_REF 129 
#define  FORM_STRING 128 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 int SIZEOF_ATTRIBUTE ; 
 scalar_t__ SIZEOF_DIE_LENGTH ; 
 scalar_t__ SIZEOF_DIE_TAG ; 
 int /*<<< orphan*/  TARGET_FT_POINTER_SIZE (struct objfile*) ; 
 int attribute_size (unsigned short) ; 
 int baseaddr ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diecount ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 int target_to_host (char*,int,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  unknown_attribute_form_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
completedieinfo (struct dieinfo *dip, struct objfile *objfile)
{
  char *diep;			/* Current pointer into raw DIE data */
  char *end;			/* Terminate DIE scan here */
  unsigned short attr;		/* Current attribute being scanned */
  unsigned short form;		/* Form of the attribute */
  int nbytes;			/* Size of next field to read */

  diecount++;
  diep = dip->die;
  end = diep + dip->die_length;
  diep += SIZEOF_DIE_LENGTH + SIZEOF_DIE_TAG;
  while (diep < end)
    {
      attr = target_to_host (diep, SIZEOF_ATTRIBUTE, GET_UNSIGNED, objfile);
      diep += SIZEOF_ATTRIBUTE;
      nbytes = attribute_size (attr);
      if (nbytes == -1)
	{
	  complaint (&symfile_complaints,
		     "DIE @ 0x%x \"%s\", unknown attribute length, skipped remaining attributes",
		     DIE_ID, DIE_NAME);
	  diep = end;
	  continue;
	}
      switch (attr)
	{
	case AT_fund_type:
	  dip->at_fund_type = target_to_host (diep, nbytes, GET_UNSIGNED,
					      objfile);
	  break;
	case AT_ordering:
	  dip->at_ordering = target_to_host (diep, nbytes, GET_UNSIGNED,
					     objfile);
	  break;
	case AT_bit_offset:
	  dip->at_bit_offset = target_to_host (diep, nbytes, GET_UNSIGNED,
					       objfile);
	  break;
	case AT_sibling:
	  dip->at_sibling = target_to_host (diep, nbytes, GET_UNSIGNED,
					    objfile);
	  break;
	case AT_stmt_list:
	  dip->at_stmt_list = target_to_host (diep, nbytes, GET_UNSIGNED,
					      objfile);
	  dip->has_at_stmt_list = 1;
	  break;
	case AT_low_pc:
	  dip->at_low_pc = target_to_host (diep, nbytes, GET_UNSIGNED,
					   objfile);
	  dip->at_low_pc += baseaddr;
	  dip->has_at_low_pc = 1;
	  break;
	case AT_high_pc:
	  dip->at_high_pc = target_to_host (diep, nbytes, GET_UNSIGNED,
					    objfile);
	  dip->at_high_pc += baseaddr;
	  break;
	case AT_language:
	  dip->at_language = target_to_host (diep, nbytes, GET_UNSIGNED,
					     objfile);
	  break;
	case AT_user_def_type:
	  dip->at_user_def_type = target_to_host (diep, nbytes,
						  GET_UNSIGNED, objfile);
	  break;
	case AT_byte_size:
	  dip->at_byte_size = target_to_host (diep, nbytes, GET_UNSIGNED,
					      objfile);
	  dip->has_at_byte_size = 1;
	  break;
	case AT_bit_size:
	  dip->at_bit_size = target_to_host (diep, nbytes, GET_UNSIGNED,
					     objfile);
	  break;
	case AT_member:
	  dip->at_member = target_to_host (diep, nbytes, GET_UNSIGNED,
					   objfile);
	  break;
	case AT_discr:
	  dip->at_discr = target_to_host (diep, nbytes, GET_UNSIGNED,
					  objfile);
	  break;
	case AT_location:
	  dip->at_location = diep;
	  break;
	case AT_mod_fund_type:
	  dip->at_mod_fund_type = diep;
	  break;
	case AT_subscr_data:
	  dip->at_subscr_data = diep;
	  break;
	case AT_mod_u_d_type:
	  dip->at_mod_u_d_type = diep;
	  break;
	case AT_element_list:
	  dip->at_element_list = diep;
	  dip->short_element_list = 0;
	  break;
	case AT_short_element_list:
	  dip->at_element_list = diep;
	  dip->short_element_list = 1;
	  break;
	case AT_discr_value:
	  dip->at_discr_value = diep;
	  break;
	case AT_string_length:
	  dip->at_string_length = diep;
	  break;
	case AT_name:
	  dip->at_name = diep;
	  break;
	case AT_comp_dir:
	  /* For now, ignore any "hostname:" portion, since gdb doesn't
	     know how to deal with it.  (FIXME). */
	  dip->at_comp_dir = strrchr (diep, ':');
	  if (dip->at_comp_dir != NULL)
	    {
	      dip->at_comp_dir++;
	    }
	  else
	    {
	      dip->at_comp_dir = diep;
	    }
	  break;
	case AT_producer:
	  dip->at_producer = diep;
	  break;
	case AT_start_scope:
	  dip->at_start_scope = target_to_host (diep, nbytes, GET_UNSIGNED,
						objfile);
	  break;
	case AT_stride_size:
	  dip->at_stride_size = target_to_host (diep, nbytes, GET_UNSIGNED,
						objfile);
	  break;
	case AT_src_info:
	  dip->at_src_info = target_to_host (diep, nbytes, GET_UNSIGNED,
					     objfile);
	  break;
	case AT_prototyped:
	  dip->at_prototyped = diep;
	  break;
	default:
	  /* Found an attribute that we are unprepared to handle.  However
	     it is specifically one of the design goals of DWARF that
	     consumers should ignore unknown attributes.  As long as the
	     form is one that we recognize (so we know how to skip it),
	     we can just ignore the unknown attribute. */
	  break;
	}
      form = FORM_FROM_ATTR (attr);
      switch (form)
	{
	case FORM_DATA2:
	  diep += 2;
	  break;
	case FORM_DATA4:
	case FORM_REF:
	  diep += 4;
	  break;
	case FORM_DATA8:
	  diep += 8;
	  break;
	case FORM_ADDR:
	  diep += TARGET_FT_POINTER_SIZE (objfile);
	  break;
	case FORM_BLOCK2:
	  diep += 2 + target_to_host (diep, nbytes, GET_UNSIGNED, objfile);
	  break;
	case FORM_BLOCK4:
	  diep += 4 + target_to_host (diep, nbytes, GET_UNSIGNED, objfile);
	  break;
	case FORM_STRING:
	  diep += strlen (diep) + 1;
	  break;
	default:
	  unknown_attribute_form_complaint (DIE_ID, DIE_NAME, form);
	  diep = end;
	  break;
	}
    }
}