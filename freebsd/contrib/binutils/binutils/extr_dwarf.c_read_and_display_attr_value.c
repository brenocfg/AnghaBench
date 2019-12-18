#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uvalue ;
struct TYPE_3__ {unsigned int max_loc_offsets; unsigned int num_loc_offsets; int* loc_offsets; int* have_frame_base; unsigned long base_address; unsigned int max_range_lists; unsigned int num_range_lists; int* range_lists; } ;
typedef  TYPE_1__ debug_info ;

/* Variables and functions */
#define  DW_ACCESS_private 222 
#define  DW_ACCESS_protected 221 
#define  DW_ACCESS_public 220 
#define  DW_ATE_address 219 
#define  DW_ATE_boolean 218 
#define  DW_ATE_complex_float 217 
#define  DW_ATE_decimal_float 216 
#define  DW_ATE_float 215 
 unsigned long DW_ATE_hi_user ; 
#define  DW_ATE_imaginary_float 214 
 unsigned long DW_ATE_lo_user ; 
#define  DW_ATE_signed 213 
#define  DW_ATE_signed_char 212 
#define  DW_ATE_unsigned 211 
#define  DW_ATE_unsigned_char 210 
#define  DW_ATE_void 209 
#define  DW_AT_accessibility 208 
#define  DW_AT_allocated 207 
#define  DW_AT_associated 206 
#define  DW_AT_calling_convention 205 
#define  DW_AT_data_location 204 
#define  DW_AT_data_member_location 203 
#define  DW_AT_encoding 202 
#define  DW_AT_frame_base 201 
#define  DW_AT_identifier_case 200 
#define  DW_AT_inline 199 
#define  DW_AT_language 198 
#define  DW_AT_location 197 
#define  DW_AT_low_pc 196 
#define  DW_AT_lower_bound 195 
#define  DW_AT_ordering 194 
#define  DW_AT_ranges 193 
#define  DW_AT_stride 192 
#define  DW_AT_upper_bound 191 
#define  DW_AT_virtuality 190 
#define  DW_AT_visibility 189 
#define  DW_AT_vtable_elem_location 188 
 unsigned long DW_CC_hi_user ; 
 unsigned long DW_CC_lo_user ; 
#define  DW_CC_nocall 187 
#define  DW_CC_normal 186 
#define  DW_CC_program 185 
#define  DW_FORM_addr 184 
#define  DW_FORM_block 183 
#define  DW_FORM_block1 182 
#define  DW_FORM_block2 181 
#define  DW_FORM_block4 180 
#define  DW_FORM_data1 179 
#define  DW_FORM_data2 178 
#define  DW_FORM_data4 177 
#define  DW_FORM_data8 176 
#define  DW_FORM_flag 175 
#define  DW_FORM_flag_present 174 
#define  DW_FORM_indirect 173 
#define  DW_FORM_ref1 172 
#define  DW_FORM_ref2 171 
#define  DW_FORM_ref4 170 
#define  DW_FORM_ref8 169 
#define  DW_FORM_ref_addr 168 
#define  DW_FORM_ref_udata 167 
#define  DW_FORM_sdata 166 
#define  DW_FORM_string 165 
#define  DW_FORM_strp 164 
#define  DW_FORM_udata 163 
#define  DW_ID_case_insensitive 162 
#define  DW_ID_case_sensitive 161 
#define  DW_ID_down_case 160 
#define  DW_ID_up_case 159 
#define  DW_INL_declared_inlined 158 
#define  DW_INL_declared_not_inlined 157 
#define  DW_INL_inlined 156 
#define  DW_INL_not_inlined 155 
#define  DW_LANG_Ada83 154 
#define  DW_LANG_Ada95 153 
#define  DW_LANG_C 152 
#define  DW_LANG_C89 151 
#define  DW_LANG_C99 150 
#define  DW_LANG_C_plus_plus 149 
#define  DW_LANG_Cobol74 148 
#define  DW_LANG_Cobol85 147 
#define  DW_LANG_D 146 
#define  DW_LANG_Fortran77 145 
#define  DW_LANG_Fortran90 144 
#define  DW_LANG_Fortran95 143 
#define  DW_LANG_Java 142 
#define  DW_LANG_Mips_Assembler 141 
#define  DW_LANG_Modula2 140 
#define  DW_LANG_ObjC 139 
#define  DW_LANG_ObjC_plus_plus 138 
#define  DW_LANG_PLI 137 
#define  DW_LANG_Pascal83 136 
#define  DW_LANG_UPC 135 
#define  DW_LANG_Upc 134 
 unsigned long DW_LANG_hi_user ; 
 unsigned long DW_LANG_lo_user ; 
#define  DW_VIRTUALITY_none 133 
#define  DW_VIRTUALITY_pure_virtual 132 
#define  DW_VIRTUALITY_virtual 131 
#define  DW_VIS_exported 130 
#define  DW_VIS_local 129 
#define  DW_VIS_qualified 128 
 char* _ (char*) ; 
 unsigned long byte_get (unsigned char*,int) ; 
 int decode_location_expression (unsigned char*,unsigned long,unsigned long,unsigned long) ; 
 unsigned char* display_block (unsigned char*,unsigned long) ; 
 scalar_t__ do_debug_loc ; 
 scalar_t__ do_debug_ranges ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fetch_indirect_string (unsigned long) ; 
 char* get_FORM_name (unsigned long) ; 
 int have_frame_base ; 
 int /*<<< orphan*/  need_base_address ; 
 scalar_t__ num_debug_info_entries ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long read_leb128 (unsigned char*,unsigned int*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  warn (char*,unsigned long) ; 
 void* xcrealloc (int*,unsigned int,int) ; 

__attribute__((used)) static unsigned char *
read_and_display_attr_value (unsigned long attribute,
			     unsigned long form,
			     unsigned char *data,
			     unsigned long cu_offset,
			     unsigned long pointer_size,
			     unsigned long offset_size,
			     int dwarf_version,
			     debug_info *debug_info_p,
			     int do_loc)
{
  unsigned long uvalue = 0;
  unsigned char *block_start = NULL;
  unsigned int bytes_read;

  switch (form)
    {
    default:
      break;

    case DW_FORM_ref_addr:
      if (dwarf_version == 2)
	{
	  uvalue = byte_get (data, pointer_size);
	  data += pointer_size;
	}
      else if (dwarf_version == 3)
	{
	  uvalue = byte_get (data, offset_size);
	  data += offset_size;
	}
      else
	{
	  error (_("Internal error: DWARF version is not 2 or 3.\n"));
	}
      break;

    case DW_FORM_addr:
      uvalue = byte_get (data, pointer_size);
      data += pointer_size;
      break;

    case DW_FORM_strp:
      uvalue = byte_get (data, offset_size);
      data += offset_size;
      break;

    case DW_FORM_flag_present:
      uvalue = 1;
      break;

    case DW_FORM_ref1:
    case DW_FORM_flag:
    case DW_FORM_data1:
      uvalue = byte_get (data++, 1);
      break;

    case DW_FORM_ref2:
    case DW_FORM_data2:
      uvalue = byte_get (data, 2);
      data += 2;
      break;

    case DW_FORM_ref4:
    case DW_FORM_data4:
      uvalue = byte_get (data, 4);
      data += 4;
      break;

    case DW_FORM_sdata:
      uvalue = read_leb128 (data, & bytes_read, 1);
      data += bytes_read;
      break;

    case DW_FORM_ref_udata:
    case DW_FORM_udata:
      uvalue = read_leb128 (data, & bytes_read, 0);
      data += bytes_read;
      break;

    case DW_FORM_indirect:
      form = read_leb128 (data, & bytes_read, 0);
      data += bytes_read;
      if (!do_loc)
	printf (" %s", get_FORM_name (form));
      return read_and_display_attr_value (attribute, form, data,
					  cu_offset, pointer_size,
					  offset_size, dwarf_version,
					  debug_info_p, do_loc);
    }

  switch (form)
    {
    case DW_FORM_ref_addr:
      if (!do_loc)
	printf (" <#%lx>", uvalue);
      break;

    case DW_FORM_ref1:
    case DW_FORM_ref2:
    case DW_FORM_ref4:
    case DW_FORM_ref_udata:
      if (!do_loc)
	printf (" <%lx>", uvalue + cu_offset);
      break;

    case DW_FORM_data4:
    case DW_FORM_addr:
      if (!do_loc)
	printf (" %#lx", uvalue);
      break;

    case DW_FORM_flag_present:
    case DW_FORM_flag:
    case DW_FORM_data1:
    case DW_FORM_data2:
    case DW_FORM_sdata:
    case DW_FORM_udata:
      if (!do_loc)
	printf (" %ld", uvalue);
      break;

    case DW_FORM_ref8:
    case DW_FORM_data8:
      if (!do_loc)
	{
	  uvalue = byte_get (data, 4);
	  printf (" %lx", uvalue);
	  printf (" %lx", (unsigned long) byte_get (data + 4, 4));
	}
      if ((do_loc || do_debug_loc || do_debug_ranges)
	  && num_debug_info_entries == 0)
	{
	  if (sizeof (uvalue) == 8)
	    uvalue = byte_get (data, 8);
	  else
	    error (_("DW_FORM_data8 is unsupported when sizeof (unsigned long) != 8\n"));
	}
      data += 8;
      break;

    case DW_FORM_string:
      if (!do_loc)
	printf (" %s", data);
      data += strlen ((char *) data) + 1;
      break;

    case DW_FORM_block:
      uvalue = read_leb128 (data, & bytes_read, 0);
      block_start = data + bytes_read;
      if (do_loc)
	data = block_start + uvalue;
      else
	data = display_block (block_start, uvalue);
      break;

    case DW_FORM_block1:
      uvalue = byte_get (data, 1);
      block_start = data + 1;
      if (do_loc)
	data = block_start + uvalue;
      else
	data = display_block (block_start, uvalue);
      break;

    case DW_FORM_block2:
      uvalue = byte_get (data, 2);
      block_start = data + 2;
      if (do_loc)
	data = block_start + uvalue;
      else
	data = display_block (block_start, uvalue);
      break;

    case DW_FORM_block4:
      uvalue = byte_get (data, 4);
      block_start = data + 4;
      if (do_loc)
	data = block_start + uvalue;
      else
	data = display_block (block_start, uvalue);
      break;

    case DW_FORM_strp:
      if (!do_loc)
	printf (_(" (indirect string, offset: 0x%lx): %s"),
		uvalue, fetch_indirect_string (uvalue));
      break;

    case DW_FORM_indirect:
      /* Handled above.  */
      break;

    default:
      warn (_("Unrecognized form: %lu\n"), form);
      break;
    }

  /* For some attributes we can display further information.  */
  if ((do_loc || do_debug_loc || do_debug_ranges)
      && num_debug_info_entries == 0)
    {
      switch (attribute)
	{
	case DW_AT_frame_base:
	  have_frame_base = 1;
	case DW_AT_location:
	case DW_AT_data_member_location:
	case DW_AT_vtable_elem_location:
	case DW_AT_allocated:
	case DW_AT_associated:
	case DW_AT_data_location:
	case DW_AT_stride:
	case DW_AT_upper_bound:
	case DW_AT_lower_bound:
	  if (form == DW_FORM_data4 || form == DW_FORM_data8)
	    {
	      /* Process location list.  */
	      unsigned int max = debug_info_p->max_loc_offsets;
	      unsigned int num = debug_info_p->num_loc_offsets;

	      if (max == 0 || num >= max)
		{
		  max += 1024;
		  debug_info_p->loc_offsets
		    = xcrealloc (debug_info_p->loc_offsets,
				 max, sizeof (*debug_info_p->loc_offsets));
		  debug_info_p->have_frame_base
		    = xcrealloc (debug_info_p->have_frame_base,
				 max, sizeof (*debug_info_p->have_frame_base));
		  debug_info_p->max_loc_offsets = max;
		}
	      debug_info_p->loc_offsets [num] = uvalue;
	      debug_info_p->have_frame_base [num] = have_frame_base;
	      debug_info_p->num_loc_offsets++;
	    }
	  break;
	
	case DW_AT_low_pc:
	  if (need_base_address)
	    debug_info_p->base_address = uvalue;
	  break;

	case DW_AT_ranges:
	  if (form == DW_FORM_data4 || form == DW_FORM_data8)
	    {
	      /* Process range list.  */
	      unsigned int max = debug_info_p->max_range_lists;
	      unsigned int num = debug_info_p->num_range_lists;

	      if (max == 0 || num >= max)
		{
		  max += 1024;
		  debug_info_p->range_lists
		    = xcrealloc (debug_info_p->range_lists,
				 max, sizeof (*debug_info_p->range_lists));
		  debug_info_p->max_range_lists = max;
		}
	      debug_info_p->range_lists [num] = uvalue;
	      debug_info_p->num_range_lists++;
	    }
	  break;

	default:
	  break;
	}
    }

  if (do_loc)
    return data;

  printf ("\t");

  switch (attribute)
    {
    case DW_AT_inline:
      switch (uvalue)
	{
	case DW_INL_not_inlined:
	  printf (_("(not inlined)"));
	  break;
	case DW_INL_inlined:
	  printf (_("(inlined)"));
	  break;
	case DW_INL_declared_not_inlined:
	  printf (_("(declared as inline but ignored)"));
	  break;
	case DW_INL_declared_inlined:
	  printf (_("(declared as inline and inlined)"));
	  break;
	default:
	  printf (_("  (Unknown inline attribute value: %lx)"), uvalue);
	  break;
	}
      break;

    case DW_AT_language:
      switch (uvalue)
	{
	  /* Ordered by the numeric value of these constants.  */
	case DW_LANG_C89:		printf ("(ANSI C)"); break;
	case DW_LANG_C:			printf ("(non-ANSI C)"); break;
	case DW_LANG_Ada83:		printf ("(Ada)"); break;
	case DW_LANG_C_plus_plus:	printf ("(C++)"); break;
	case DW_LANG_Cobol74:		printf ("(Cobol 74)"); break;
	case DW_LANG_Cobol85:		printf ("(Cobol 85)"); break;
	case DW_LANG_Fortran77:		printf ("(FORTRAN 77)"); break;
	case DW_LANG_Fortran90:		printf ("(Fortran 90)"); break;
	case DW_LANG_Pascal83:		printf ("(ANSI Pascal)"); break;
	case DW_LANG_Modula2:		printf ("(Modula 2)"); break;
	  /* DWARF 2.1 values.	*/
	case DW_LANG_Java:		printf ("(Java)"); break;
	case DW_LANG_C99:		printf ("(ANSI C99)"); break;
	case DW_LANG_Ada95:		printf ("(ADA 95)"); break;
	case DW_LANG_Fortran95:		printf ("(Fortran 95)"); break;
	  /* DWARF 3 values.  */
	case DW_LANG_PLI:		printf ("(PLI)"); break;
	case DW_LANG_ObjC:		printf ("(Objective C)"); break;
	case DW_LANG_ObjC_plus_plus:	printf ("(Objective C++)"); break;
	case DW_LANG_UPC:		printf ("(Unified Parallel C)"); break;
	case DW_LANG_D:			printf ("(D)"); break;
	  /* MIPS extension.  */
	case DW_LANG_Mips_Assembler:	printf ("(MIPS assembler)"); break;
	  /* UPC extension.  */
	case DW_LANG_Upc:		printf ("(Unified Parallel C)"); break;
	default:
	  if (uvalue >= DW_LANG_lo_user && uvalue <= DW_LANG_hi_user)
	    printf ("(implementation defined: %lx)", uvalue);
	  else
	    printf ("(Unknown: %lx)", uvalue);
	  break;
	}
      break;

    case DW_AT_encoding:
      switch (uvalue)
	{
	case DW_ATE_void:		printf ("(void)"); break;
	case DW_ATE_address:		printf ("(machine address)"); break;
	case DW_ATE_boolean:		printf ("(boolean)"); break;
	case DW_ATE_complex_float:	printf ("(complex float)"); break;
	case DW_ATE_float:		printf ("(float)"); break;
	case DW_ATE_signed:		printf ("(signed)"); break;
	case DW_ATE_signed_char:	printf ("(signed char)"); break;
	case DW_ATE_unsigned:		printf ("(unsigned)"); break;
	case DW_ATE_unsigned_char:	printf ("(unsigned char)"); break;
	  /* DWARF 2.1 value.  */
	case DW_ATE_imaginary_float:	printf ("(imaginary float)"); break;
	case DW_ATE_decimal_float:	printf ("(decimal float)"); break;
	default:
	  if (uvalue >= DW_ATE_lo_user
	      && uvalue <= DW_ATE_hi_user)
	    printf ("(user defined type)");
	  else
	    printf ("(unknown type)");
	  break;
	}
      break;

    case DW_AT_accessibility:
      switch (uvalue)
	{
	case DW_ACCESS_public:		printf ("(public)"); break;
	case DW_ACCESS_protected:	printf ("(protected)"); break;
	case DW_ACCESS_private:		printf ("(private)"); break;
	default:
	  printf ("(unknown accessibility)");
	  break;
	}
      break;

    case DW_AT_visibility:
      switch (uvalue)
	{
	case DW_VIS_local:		printf ("(local)"); break;
	case DW_VIS_exported:		printf ("(exported)"); break;
	case DW_VIS_qualified:		printf ("(qualified)"); break;
	default:			printf ("(unknown visibility)"); break;
	}
      break;

    case DW_AT_virtuality:
      switch (uvalue)
	{
	case DW_VIRTUALITY_none:	printf ("(none)"); break;
	case DW_VIRTUALITY_virtual:	printf ("(virtual)"); break;
	case DW_VIRTUALITY_pure_virtual:printf ("(pure_virtual)"); break;
	default:			printf ("(unknown virtuality)"); break;
	}
      break;

    case DW_AT_identifier_case:
      switch (uvalue)
	{
	case DW_ID_case_sensitive:	printf ("(case_sensitive)"); break;
	case DW_ID_up_case:		printf ("(up_case)"); break;
	case DW_ID_down_case:		printf ("(down_case)"); break;
	case DW_ID_case_insensitive:	printf ("(case_insensitive)"); break;
	default:			printf ("(unknown case)"); break;
	}
      break;

    case DW_AT_calling_convention:
      switch (uvalue)
	{
	case DW_CC_normal:	printf ("(normal)"); break;
	case DW_CC_program:	printf ("(program)"); break;
	case DW_CC_nocall:	printf ("(nocall)"); break;
	default:
	  if (uvalue >= DW_CC_lo_user
	      && uvalue <= DW_CC_hi_user)
	    printf ("(user defined)");
	  else
	    printf ("(unknown convention)");
	}
      break;

    case DW_AT_ordering:
      switch (uvalue)
	{
	case -1: printf ("(undefined)"); break;
	case 0:  printf ("(row major)"); break;
	case 1:  printf ("(column major)"); break;
	}
      break;

    case DW_AT_frame_base:
      have_frame_base = 1;
    case DW_AT_location:
    case DW_AT_data_member_location:
    case DW_AT_vtable_elem_location:
    case DW_AT_allocated:
    case DW_AT_associated:
    case DW_AT_data_location:
    case DW_AT_stride:
    case DW_AT_upper_bound:
    case DW_AT_lower_bound:
      if (block_start)
	{
	  int need_frame_base;

	  printf ("(");
	  need_frame_base = decode_location_expression (block_start,
							pointer_size,
							uvalue,
							cu_offset);
	  printf (")");
	  if (need_frame_base && !have_frame_base)
	    printf (_(" [without DW_AT_frame_base]"));
	}
      else if (form == DW_FORM_data4 || form == DW_FORM_data8)
	printf (_("(location list)"));

      break;

    default:
      break;
    }

  return data;
}