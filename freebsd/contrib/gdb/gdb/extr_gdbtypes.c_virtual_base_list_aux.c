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
struct vbase {struct vbase* next; struct type* vbasetype; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 struct vbase* current_vbase_list ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
virtual_base_list_aux (struct type *dclass)
{
  struct vbase *tmp_vbase;
  int i;

  if (TYPE_CODE (dclass) != TYPE_CODE_CLASS)
    return;

  for (i = 0; i < TYPE_N_BASECLASSES (dclass); i++)
    {
      /* Recurse on this ancestor, first */
      virtual_base_list_aux (TYPE_FIELD_TYPE (dclass, i));

      /* If this current base is itself virtual, add it to the list */
      if (BASETYPE_VIA_VIRTUAL (dclass, i))
	{
	  struct type *basetype = TYPE_FIELD_TYPE (dclass, i);

	  /* Check if base already recorded */
	  tmp_vbase = current_vbase_list;
	  while (tmp_vbase)
	    {
	      if (tmp_vbase->vbasetype == basetype)
		break;		/* found it */
	      tmp_vbase = tmp_vbase->next;
	    }

	  if (!tmp_vbase)	/* normal exit from loop */
	    {
	      /* Allocate new item for this virtual base */
	      tmp_vbase = (struct vbase *) xmalloc (sizeof (struct vbase));

	      /* Stick it on at the end of the list */
	      tmp_vbase->vbasetype = basetype;
	      tmp_vbase->next = current_vbase_list;
	      current_vbase_list = tmp_vbase;
	    }
	}			/* if virtual */
    }				/* for loop over bases */
}