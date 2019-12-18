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
struct dieinfo {scalar_t__ die_length; int die_tag; scalar_t__ at_sibling; int /*<<< orphan*/  has_at_low_pc; void* at_high_pc; void* at_low_pc; } ;

/* Variables and functions */
 scalar_t__ SIZEOF_DIE_LENGTH ; 
 void* SMASH_TEXT_ADDRESS (void*) ; 
#define  TAG_array_type 139 
#define  TAG_class_type 138 
#define  TAG_compile_unit 137 
#define  TAG_enumeration_type 136 
#define  TAG_global_subroutine 135 
#define  TAG_lexical_block 134 
 int TAG_padding ; 
#define  TAG_pointer_type 133 
#define  TAG_string_type 132 
#define  TAG_structure_type 131 
#define  TAG_subroutine 130 
#define  TAG_subroutine_type 129 
#define  TAG_union_type 128 
 int /*<<< orphan*/  basicdieinfo (struct dieinfo*,char*,struct objfile*) ; 
 int /*<<< orphan*/  completedieinfo (struct dieinfo*,struct objfile*) ; 
 int /*<<< orphan*/ * current_subfile ; 
 int /*<<< orphan*/  dbbase ; 
 int /*<<< orphan*/  dbroff ; 
 int /*<<< orphan*/  dwarf_read_array_type (struct dieinfo*) ; 
 int /*<<< orphan*/  new_symbol (struct dieinfo*,struct objfile*) ; 
 int /*<<< orphan*/  read_enumeration (struct dieinfo*,char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  read_file_scope (struct dieinfo*,char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  read_func_scope (struct dieinfo*,char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  read_lexical_block_scope (struct dieinfo*,char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  read_structure_scope (struct dieinfo*,char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  read_subroutine_type (struct dieinfo*,char*,char*) ; 
 int /*<<< orphan*/  read_tag_pointer_type (struct dieinfo*) ; 
 int /*<<< orphan*/  read_tag_string_type (struct dieinfo*) ; 

__attribute__((used)) static void
process_dies (char *thisdie, char *enddie, struct objfile *objfile)
{
  char *nextdie;
  struct dieinfo di;

  while (thisdie < enddie)
    {
      basicdieinfo (&di, thisdie, objfile);
      if (di.die_length < SIZEOF_DIE_LENGTH)
	{
	  break;
	}
      else if (di.die_tag == TAG_padding)
	{
	  nextdie = thisdie + di.die_length;
	}
      else
	{
	  completedieinfo (&di, objfile);
	  if (di.at_sibling != 0)
	    {
	      nextdie = dbbase + di.at_sibling - dbroff;
	    }
	  else
	    {
	      nextdie = thisdie + di.die_length;
	    }
	  /* I think that these are always text, not data, addresses.  */
	  di.at_low_pc = SMASH_TEXT_ADDRESS (di.at_low_pc);
	  di.at_high_pc = SMASH_TEXT_ADDRESS (di.at_high_pc);
	  switch (di.die_tag)
	    {
	    case TAG_compile_unit:
	      /* Skip Tag_compile_unit if we are already inside a compilation
	         unit, we are unable to handle nested compilation units
	         properly (FIXME).  */
	      if (current_subfile == NULL)
		read_file_scope (&di, thisdie, nextdie, objfile);
	      else
		nextdie = thisdie + di.die_length;
	      break;
	    case TAG_global_subroutine:
	    case TAG_subroutine:
	      if (di.has_at_low_pc)
		{
		  read_func_scope (&di, thisdie, nextdie, objfile);
		}
	      break;
	    case TAG_lexical_block:
	      read_lexical_block_scope (&di, thisdie, nextdie, objfile);
	      break;
	    case TAG_class_type:
	    case TAG_structure_type:
	    case TAG_union_type:
	      read_structure_scope (&di, thisdie, nextdie, objfile);
	      break;
	    case TAG_enumeration_type:
	      read_enumeration (&di, thisdie, nextdie, objfile);
	      break;
	    case TAG_subroutine_type:
	      read_subroutine_type (&di, thisdie, nextdie);
	      break;
	    case TAG_array_type:
	      dwarf_read_array_type (&di);
	      break;
	    case TAG_pointer_type:
	      read_tag_pointer_type (&di);
	      break;
	    case TAG_string_type:
	      read_tag_string_type (&di);
	      break;
	    default:
	      new_symbol (&di, objfile);
	      break;
	    }
	}
      thisdie = nextdie;
    }
}