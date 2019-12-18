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
struct dieinfo {int at_byte_size; int /*<<< orphan*/  die_ref; scalar_t__ has_at_byte_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  FT_INTEGER ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_UNDEF ; 
 struct type* alloc_utype (int /*<<< orphan*/ ,struct type*) ; 
 struct type* create_range_type (struct type*,struct type*,unsigned long,unsigned long) ; 
 struct type* create_string_type (struct type*,struct type*) ; 
 int /*<<< orphan*/  current_objfile ; 
 int /*<<< orphan*/  dup_user_type_definition_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* dwarf_fundamental_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* lookup_utype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_tag_string_type (struct dieinfo *dip)
{
  struct type *utype;
  struct type *indextype;
  struct type *rangetype;
  unsigned long lowbound = 0;
  unsigned long highbound;

  if (dip->has_at_byte_size)
    {
      /* A fixed bounds string */
      highbound = dip->at_byte_size - 1;
    }
  else
    {
      /* A varying length string.  Stub for now.  (FIXME) */
      highbound = 1;
    }
  indextype = dwarf_fundamental_type (current_objfile, FT_INTEGER);
  rangetype = create_range_type ((struct type *) NULL, indextype, lowbound,
				 highbound);

  utype = lookup_utype (dip->die_ref);
  if (utype == NULL)
    {
      /* No type defined, go ahead and create a blank one to use. */
      utype = alloc_utype (dip->die_ref, (struct type *) NULL);
    }
  else
    {
      /* Already a type in our slot due to a forward reference. Make sure it
         is a blank one.  If not, complain and leave it alone. */
      if (TYPE_CODE (utype) != TYPE_CODE_UNDEF)
	{
	  dup_user_type_definition_complaint (DIE_ID, DIE_NAME);
	  return;
	}
    }

  /* Create the string type using the blank type we either found or created. */
  utype = create_string_type (utype, rangetype);
}