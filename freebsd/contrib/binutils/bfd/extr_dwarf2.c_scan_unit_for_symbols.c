#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct varinfo {scalar_t__ tag; int stack; scalar_t__ line; int /*<<< orphan*/  addr; void* file; int /*<<< orphan*/ * name; struct varinfo* prev_var; } ;
struct funcinfo {scalar_t__ tag; scalar_t__ caller_line; scalar_t__ line; int /*<<< orphan*/  arange; void* file; int /*<<< orphan*/ * name; void* caller_file; struct funcinfo* caller_func; struct funcinfo* prev_func; } ;
struct comp_unit {int addr_size; int /*<<< orphan*/ * abfd; int /*<<< orphan*/  line_table; struct varinfo* variable_table; struct funcinfo* function_table; int /*<<< orphan*/  abbrevs; int /*<<< orphan*/ * first_child_die_ptr; } ;
struct TYPE_3__ {scalar_t__ val; TYPE_2__* blk; int /*<<< orphan*/ * str; } ;
struct attribute {int name; TYPE_1__ u; int /*<<< orphan*/  form; } ;
struct abbrev_info {scalar_t__ tag; unsigned int num_attrs; scalar_t__ has_children; int /*<<< orphan*/ * attrs; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
#define  DW_AT_MIPS_linkage_name 143 
#define  DW_AT_abstract_origin 142 
#define  DW_AT_call_file 141 
#define  DW_AT_call_line 140 
#define  DW_AT_decl_file 139 
#define  DW_AT_decl_line 138 
#define  DW_AT_external 137 
#define  DW_AT_high_pc 136 
#define  DW_AT_location 135 
#define  DW_AT_low_pc 134 
#define  DW_AT_name 133 
#define  DW_AT_ranges 132 
#define  DW_FORM_block 131 
#define  DW_FORM_block1 130 
#define  DW_FORM_block2 129 
#define  DW_FORM_block4 128 
 int /*<<< orphan*/  DW_OP_addr ; 
 scalar_t__ DW_TAG_entry_point ; 
 scalar_t__ DW_TAG_inlined_subroutine ; 
 scalar_t__ DW_TAG_subprogram ; 
 scalar_t__ DW_TAG_variable ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  arange_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/  bfd_get (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct funcinfo** bfd_malloc (int) ; 
 struct funcinfo** bfd_realloc (struct funcinfo**,int) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 void* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 void* concat_filename (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * find_abstract_instance_name (struct comp_unit*,scalar_t__) ; 
 int /*<<< orphan*/  free (struct funcinfo**) ; 
 struct abbrev_info* lookup_abbrev (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_attribute (struct attribute*,int /*<<< orphan*/ *,struct comp_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_rangelist (struct comp_unit*,int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int read_unsigned_leb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bfd_boolean
scan_unit_for_symbols (struct comp_unit *unit)
{
  bfd *abfd = unit->abfd;
  bfd_byte *info_ptr = unit->first_child_die_ptr;
  int nesting_level = 1;
  struct funcinfo **nested_funcs;
  int nested_funcs_size;

  /* Maintain a stack of in-scope functions and inlined functions, which we
     can use to set the caller_func field.  */
  nested_funcs_size = 32;
  nested_funcs = bfd_malloc (nested_funcs_size * sizeof (struct funcinfo *));
  if (nested_funcs == NULL)
    return FALSE;
  nested_funcs[nesting_level] = 0;

  while (nesting_level)
    {
      unsigned int abbrev_number, bytes_read, i;
      struct abbrev_info *abbrev;
      struct attribute attr;
      struct funcinfo *func;
      struct varinfo *var;
      bfd_vma low_pc = 0;
      bfd_vma high_pc = 0;

      abbrev_number = read_unsigned_leb128 (abfd, info_ptr, &bytes_read);
      info_ptr += bytes_read;

      if (! abbrev_number)
	{
	  nesting_level--;
	  continue;
	}

      abbrev = lookup_abbrev (abbrev_number,unit->abbrevs);
      if (! abbrev)
	{
	  (*_bfd_error_handler) (_("Dwarf Error: Could not find abbrev number %u."),
			     abbrev_number);
	  bfd_set_error (bfd_error_bad_value);
	  free (nested_funcs);
	  return FALSE;
	}

      var = NULL;
      if (abbrev->tag == DW_TAG_subprogram
	  || abbrev->tag == DW_TAG_entry_point
	  || abbrev->tag == DW_TAG_inlined_subroutine)
	{
	  bfd_size_type amt = sizeof (struct funcinfo);
	  func = bfd_zalloc (abfd, amt);
	  func->tag = abbrev->tag;
	  func->prev_func = unit->function_table;
	  unit->function_table = func;

	  if (func->tag == DW_TAG_inlined_subroutine)
	    for (i = nesting_level - 1; i >= 1; i--)
	      if (nested_funcs[i])
		{
		  func->caller_func = nested_funcs[i];
		  break;
		}
	  nested_funcs[nesting_level] = func;
	}
      else
	{
	  func = NULL;
	  if (abbrev->tag == DW_TAG_variable)
	    {
	      bfd_size_type amt = sizeof (struct varinfo);
	      var = bfd_zalloc (abfd, amt);
	      var->tag = abbrev->tag;
	      var->stack = 1;
	      var->prev_var = unit->variable_table;
	      unit->variable_table = var;
	    }

	  /* No inline function in scope at this nesting level.  */
	  nested_funcs[nesting_level] = 0;
	}

      for (i = 0; i < abbrev->num_attrs; ++i)
	{
	  info_ptr = read_attribute (&attr, &abbrev->attrs[i], unit, info_ptr);

	  if (func)
	    {
	      switch (attr.name)
		{
		case DW_AT_call_file:
		  func->caller_file = concat_filename (unit->line_table, attr.u.val);
		  break;

		case DW_AT_call_line:
		  func->caller_line = attr.u.val;
		  break;

		case DW_AT_abstract_origin:
		  func->name = find_abstract_instance_name (unit, attr.u.val);
		  break;

		case DW_AT_name:
		  /* Prefer DW_AT_MIPS_linkage_name over DW_AT_name.  */
		  if (func->name == NULL)
		    func->name = attr.u.str;
		  break;

		case DW_AT_MIPS_linkage_name:
		  func->name = attr.u.str;
		  break;

		case DW_AT_low_pc:
		  low_pc = attr.u.val;
		  break;

		case DW_AT_high_pc:
		  high_pc = attr.u.val;
		  break;

		case DW_AT_ranges:
		  read_rangelist (unit, &func->arange, attr.u.val);
		  break;

		case DW_AT_decl_file:
		  func->file = concat_filename (unit->line_table,
						attr.u.val);
		  break;

		case DW_AT_decl_line:
		  func->line = attr.u.val;
		  break;

		default:
		  break;
		}
	    }
	  else if (var)
	    {
	      switch (attr.name)
		{
		case DW_AT_name:
		  var->name = attr.u.str;
		  break;

		case DW_AT_decl_file:
		  var->file = concat_filename (unit->line_table,
					       attr.u.val);
		  break;

		case DW_AT_decl_line:
		  var->line = attr.u.val;
		  break;

		case DW_AT_external:
		  if (attr.u.val != 0)
		    var->stack = 0;
		  break;

		case DW_AT_location:
		  switch (attr.form)
		    {
		    case DW_FORM_block:
		    case DW_FORM_block1:
		    case DW_FORM_block2:
		    case DW_FORM_block4:
		      if (*attr.u.blk->data == DW_OP_addr)
			{
			  var->stack = 0;

			  /* Verify that DW_OP_addr is the only opcode in the
			     location, in which case the block size will be 1
			     plus the address size.  */
			  /* ??? For TLS variables, gcc can emit
			     DW_OP_addr <addr> DW_OP_GNU_push_tls_address
			     which we don't handle here yet.  */
			  if (attr.u.blk->size == unit->addr_size + 1U)
			    var->addr = bfd_get (unit->addr_size * 8,
						 unit->abfd,
						 attr.u.blk->data + 1);
			}
		      break;

		    default:
		      break;
		    }
		  break;

		default:
		  break;
		}
	    }
	}

      if (func && high_pc != 0)
	{
	  arange_add (unit->abfd, &func->arange, low_pc, high_pc);
	}

      if (abbrev->has_children)
	{
	  nesting_level++;

	  if (nesting_level >= nested_funcs_size)
	    {
	      struct funcinfo **tmp;

	      nested_funcs_size *= 2;
	      tmp = bfd_realloc (nested_funcs,
				 (nested_funcs_size
				  * sizeof (struct funcinfo *)));
	      if (tmp == NULL)
		{
		  free (nested_funcs);
		  return FALSE;
		}
	      nested_funcs = tmp;
	    }
	  nested_funcs[nesting_level] = 0;
	}
    }

  free (nested_funcs);
  return TRUE;
}