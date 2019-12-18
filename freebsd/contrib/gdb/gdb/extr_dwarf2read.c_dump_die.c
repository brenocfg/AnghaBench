#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct die_info {unsigned int num_attrs; TYPE_1__* attrs; int /*<<< orphan*/ * child; int /*<<< orphan*/  offset; int /*<<< orphan*/  abbrev; int /*<<< orphan*/  tag; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int form; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_ADDR (TYPE_1__*) ; 
 TYPE_3__* DW_BLOCK (TYPE_1__*) ; 
#define  DW_FORM_addr 147 
#define  DW_FORM_block 146 
#define  DW_FORM_block1 145 
#define  DW_FORM_block2 144 
#define  DW_FORM_block4 143 
#define  DW_FORM_data1 142 
#define  DW_FORM_data2 141 
#define  DW_FORM_data4 140 
#define  DW_FORM_data8 139 
#define  DW_FORM_flag 138 
#define  DW_FORM_flag_present 137 
#define  DW_FORM_indirect 136 
#define  DW_FORM_ref1 135 
#define  DW_FORM_ref2 134 
#define  DW_FORM_ref4 133 
#define  DW_FORM_ref_addr 132 
#define  DW_FORM_sdata 131 
#define  DW_FORM_string 130 
#define  DW_FORM_strp 129 
#define  DW_FORM_udata 128 
 char* DW_STRING (TYPE_1__*) ; 
 int /*<<< orphan*/  DW_UNSND (TYPE_1__*) ; 
 int /*<<< orphan*/  dwarf_attr_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_bool_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_form_name (int) ; 
 int /*<<< orphan*/  dwarf_tag_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_die (struct die_info *die)
{
  unsigned int i;

  fprintf_unfiltered (gdb_stderr, "Die: %s (abbrev = %d, offset = %d)\n",
	   dwarf_tag_name (die->tag), die->abbrev, die->offset);
  fprintf_unfiltered (gdb_stderr, "\thas children: %s\n",
	   dwarf_bool_name (die->child != NULL));

  fprintf_unfiltered (gdb_stderr, "\tattributes:\n");
  for (i = 0; i < die->num_attrs; ++i)
    {
      fprintf_unfiltered (gdb_stderr, "\t\t%s (%s) ",
	       dwarf_attr_name (die->attrs[i].name),
	       dwarf_form_name (die->attrs[i].form));
      switch (die->attrs[i].form)
	{
	case DW_FORM_ref_addr:
	case DW_FORM_addr:
	  fprintf_unfiltered (gdb_stderr, "address: ");
	  print_address_numeric (DW_ADDR (&die->attrs[i]), 1, gdb_stderr);
	  break;
	case DW_FORM_block2:
	case DW_FORM_block4:
	case DW_FORM_block:
	case DW_FORM_block1:
	  fprintf_unfiltered (gdb_stderr, "block: size %d", DW_BLOCK (&die->attrs[i])->size);
	  break;
	case DW_FORM_data1:
	case DW_FORM_data2:
	case DW_FORM_data4:
	case DW_FORM_data8:
	case DW_FORM_ref1:
	case DW_FORM_ref2:
	case DW_FORM_ref4:
	case DW_FORM_udata:
	case DW_FORM_sdata:
	  fprintf_unfiltered (gdb_stderr, "constant: %ld", DW_UNSND (&die->attrs[i]));
	  break;
	case DW_FORM_string:
	case DW_FORM_strp:
	  fprintf_unfiltered (gdb_stderr, "string: \"%s\"",
		   DW_STRING (&die->attrs[i])
		   ? DW_STRING (&die->attrs[i]) : "");
	  break;
	case DW_FORM_flag:
	  if (DW_UNSND (&die->attrs[i]))
	    fprintf_unfiltered (gdb_stderr, "flag: TRUE");
	  else
	    fprintf_unfiltered (gdb_stderr, "flag: FALSE");
	  break;
	case DW_FORM_flag_present:
	  fprintf_unfiltered (gdb_stderr, "flag: TRUE");
	  break;
	case DW_FORM_indirect:
	  /* the reader will have reduced the indirect form to
	     the "base form" so this form should not occur */
	  fprintf_unfiltered (gdb_stderr, "unexpected attribute form: DW_FORM_indirect");
	  break;
	default:
	  fprintf_unfiltered (gdb_stderr, "unsupported attribute form: %d.",
		   die->attrs[i].form);
	}
      fprintf_unfiltered (gdb_stderr, "\n");
    }
}