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
struct dieinfo {scalar_t__ at_ordering; char* at_subscr_data; int /*<<< orphan*/  die_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_subscr_data ; 
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 scalar_t__ ORD_row_major ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_UNDEF ; 
 int /*<<< orphan*/  alloc_utype (int /*<<< orphan*/ ,struct type*) ; 
 int attribute_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_objfile ; 
 struct type* decode_subscript_data_item (char*,char*) ; 
 int /*<<< orphan*/  dup_user_type_definition_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* lookup_utype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 unsigned short target_to_host (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwarf_read_array_type (struct dieinfo *dip)
{
  struct type *type;
  struct type *utype;
  char *sub;
  char *subend;
  unsigned short blocksz;
  int nbytes;

  if (dip->at_ordering != ORD_row_major)
    {
      /* FIXME:  Can gdb even handle column major arrays? */
      complaint (&symfile_complaints,
		 "DIE @ 0x%x \"%s\", array not row major; not handled correctly",
		 DIE_ID, DIE_NAME);
    }
  sub = dip->at_subscr_data;
  if (sub != NULL)
    {
      nbytes = attribute_size (AT_subscr_data);
      blocksz = target_to_host (sub, nbytes, GET_UNSIGNED, current_objfile);
      subend = sub + nbytes + blocksz;
      sub += nbytes;
      type = decode_subscript_data_item (sub, subend);
      utype = lookup_utype (dip->die_ref);
      if (utype == NULL)
	{
	  /* Install user defined type that has not been referenced yet. */
	  alloc_utype (dip->die_ref, type);
	}
      else if (TYPE_CODE (utype) == TYPE_CODE_UNDEF)
	{
	  /* Ick!  A forward ref has already generated a blank type in our
	     slot, and this type probably already has things pointing to it
	     (which is what caused it to be created in the first place).
	     If it's just a place holder we can plop our fully defined type
	     on top of it.  We can't recover the space allocated for our
	     new type since it might be on an obstack, but we could reuse
	     it if we kept a list of them, but it might not be worth it
	     (FIXME). */
	  *utype = *type;
	}
      else
	{
	  /* Double ick!  Not only is a type already in our slot, but
	     someone has decorated it.  Complain and leave it alone. */
	  dup_user_type_definition_complaint (DIE_ID, DIE_NAME);
	}
    }
}