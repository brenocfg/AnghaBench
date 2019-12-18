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
struct dwarf2_cu {scalar_t__ language; } ;
struct die_info {int tag; int /*<<< orphan*/ * type; struct die_info* parent; } ;

/* Variables and functions */
#define  DW_TAG_class_type 130 
#define  DW_TAG_namespace 129 
#define  DW_TAG_structure_type 128 
 char* TYPE_TAG_NAME (int /*<<< orphan*/ *) ; 
 char* determine_class_name (struct die_info*,struct dwarf2_cu*) ; 
 scalar_t__ language_cplus ; 
 int /*<<< orphan*/  namespace_name (struct die_info*,int*,struct dwarf2_cu*) ; 
 char const* processing_current_prefix ; 
 char* typename_concat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
determine_prefix (struct die_info *die, struct dwarf2_cu *cu)
{
  struct die_info *parent;

  if (cu->language != language_cplus)
    return NULL;

  parent = die->parent;

  if (parent == NULL)
    {
      return xstrdup ("");
    }
  else
    {
      switch (parent->tag) {
      case DW_TAG_namespace:
	{
	  /* FIXME: carlton/2004-03-05: Should I follow extension dies
	     before doing this check?  */
	  if (parent->type != NULL && TYPE_TAG_NAME (parent->type) != NULL)
	    {
	      return xstrdup (TYPE_TAG_NAME (parent->type));
	    }
	  else
	    {
	      int dummy;
	      char *parent_prefix = determine_prefix (parent, cu);
	      char *retval = typename_concat (parent_prefix,
					      namespace_name (parent, &dummy,
							      cu));
	      xfree (parent_prefix);
	      return retval;
	    }
	}
	break;
      case DW_TAG_class_type:
      case DW_TAG_structure_type:
	{
	  if (parent->type != NULL && TYPE_TAG_NAME (parent->type) != NULL)
	    {
	      return xstrdup (TYPE_TAG_NAME (parent->type));
	    }
	  else
	    {
	      const char *old_prefix = processing_current_prefix;
	      char *new_prefix = determine_prefix (parent, cu);
	      char *retval;

	      processing_current_prefix = new_prefix;
	      retval = determine_class_name (parent, cu);
	      processing_current_prefix = old_prefix;

	      xfree (new_prefix);
	      return retval;
	    }
	}
      default:
	return determine_prefix (parent, cu);
      }
    }
}