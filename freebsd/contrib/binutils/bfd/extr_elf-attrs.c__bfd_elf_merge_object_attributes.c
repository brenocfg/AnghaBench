#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i; char* s; } ;
struct TYPE_4__ {scalar_t__ tag; TYPE_2__ attr; struct TYPE_4__* next; } ;
typedef  TYPE_1__ obj_attribute_list ;
typedef  TYPE_2__ obj_attribute ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int OBJ_ATTR_FIRST ; 
 int OBJ_ATTR_LAST ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ Tag_compatibility ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  bfd_elf_add_proc_attr_compat (int /*<<< orphan*/ *,int,char*) ; 
 TYPE_1__** elf_other_obj_attributes (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

bfd_boolean
_bfd_elf_merge_object_attributes (bfd *ibfd, bfd *obfd)
{
  obj_attribute *in_attr;
  obj_attribute *out_attr;
  obj_attribute_list *in_list;
  obj_attribute_list *out_list;
  int vendor;

  /* The only common attribute is currently Tag_compatibility,
     accepted in both processor and "gnu" sections.  */
  for (vendor = OBJ_ATTR_FIRST; vendor <= OBJ_ATTR_LAST; vendor++)
    {
      in_list = elf_other_obj_attributes (ibfd)[vendor];
      out_list = elf_other_obj_attributes (ibfd)[vendor];
      while (in_list && in_list->tag == Tag_compatibility)
	{
	  in_attr = &in_list->attr;
	  if (in_attr->i == 0)
	    continue;
	  if (in_attr->i == 1 && strcmp (in_attr->s, "gnu") != 0)
	    {
	      _bfd_error_handler
		(_("ERROR: %B: Must be processed by '%s' toolchain"),
		 ibfd, in_attr->s);
	      return FALSE;
	    }
	  if (!out_list || out_list->tag != Tag_compatibility
	      || strcmp (in_attr->s, out_list->attr.s) != 0)
	    {
	      /* Add this compatibility tag to the output.  */
	      bfd_elf_add_proc_attr_compat (obfd, in_attr->i, in_attr->s);
	      continue;
	    }
	  out_attr = &out_list->attr;
	  /* Check all the input tags with the same identifier.  */
	  for (;;)
	    {
	      if (out_list->tag != Tag_compatibility
		  || in_attr->i != out_attr->i
		  || strcmp (in_attr->s, out_attr->s) != 0)
		{
		  _bfd_error_handler
		    (_("ERROR: %B: Incompatible object tag '%s':%d"),
		     ibfd, in_attr->s, in_attr->i);
		  return FALSE;
		}
	      in_list = in_list->next;
	      if (in_list->tag != Tag_compatibility
		  || strcmp (in_attr->s, in_list->attr.s) != 0)
		break;
	      in_attr = &in_list->attr;
	      out_list = out_list->next;
	      if (out_list)
		out_attr = &out_list->attr;
	    }

	  /* Check the output doesn't have extra tags with this identifier.  */
	  if (out_list && out_list->tag == Tag_compatibility
	      && strcmp (in_attr->s, out_list->attr.s) == 0)
	    {
	      _bfd_error_handler
		(_("ERROR: %B: Incompatible object tag '%s':%d"),
		 ibfd, in_attr->s, out_list->attr.i);
	      return FALSE;
	    }
	}
    }

  return TRUE;
}