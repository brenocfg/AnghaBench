#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* sorted; int /*<<< orphan*/ * exclude_name_list; int /*<<< orphan*/  name; } ;
struct wildcard_list {TYPE_1__ spec; int /*<<< orphan*/ * next; } ;
struct section_name_struct {scalar_t__ vma; int ok_to_load; struct section_name_struct* next; int /*<<< orphan*/  name; int /*<<< orphan*/  alias; int /*<<< orphan*/ * subalign; int /*<<< orphan*/ * align; } ;
typedef  int /*<<< orphan*/  etree_type ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NAME ; 
 struct section_name_struct* address ; 
 struct section_name_struct* alias ; 
 struct section_name_struct* alignment ; 
 scalar_t__ base ; 
 int done_tree ; 
 scalar_t__ exp_nameop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lang_add_wild (int /*<<< orphan*/ *,struct wildcard_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_enter_output_section_statement (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_leave_output_section_statement (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mri_add_to_list (struct section_name_struct**,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noload_section ; 
 void* none ; 
 struct section_name_struct* only_load ; 
 struct section_name_struct* order ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct section_name_struct* subalignment ; 
 struct wildcard_list* xmalloc (int) ; 

void
mri_draw_tree (void)
{
  if (done_tree)
    return;

  /* Now build the statements for the ldlang machine.  */

  /* Attach the addresses of any which have addresses,
     and add the ones not mentioned.  */
  if (address != NULL)
    {
      struct section_name_struct *alist;
      struct section_name_struct *olist;

      if (order == NULL)
	order = address;

      for (alist = address;
	   alist != NULL;
	   alist = alist->next)
	{
	  int done = 0;

	  for (olist = order; done == 0 && olist != NULL; olist = olist->next)
	    {
	      if (strcmp (alist->name, olist->name) == 0)
		{
		  olist->vma = alist->vma;
		  done = 1;
		}
	    }

	  if (!done)
	    {
	      /* Add this onto end of order list.  */
	      mri_add_to_list (&order, alist->name, alist->vma, 0, 0, 0);
	    }
	}
    }

  /* If we're only supposed to load a subset of them in, then prune
     the list.  */
  if (only_load != NULL)
    {
      struct section_name_struct *ptr1;
      struct section_name_struct *ptr2;

      if (order == NULL)
	order = only_load;

      /* See if this name is in the list, if it is then we can load it.  */
      for (ptr1 = only_load; ptr1; ptr1 = ptr1->next)
	for (ptr2 = order; ptr2; ptr2 = ptr2->next)
	  if (strcmp (ptr2->name, ptr1->name) == 0)
	    ptr2->ok_to_load = 1;
    }
  else
    {
      /* No only load list, so everything is ok to load.  */
      struct section_name_struct *ptr;

      for (ptr = order; ptr; ptr = ptr->next)
	ptr->ok_to_load = 1;
    }

  /* Create the order of sections to load.  */
  if (order != NULL)
    {
      /* Been told to output the sections in a certain order.  */
      struct section_name_struct *p = order;

      while (p)
	{
	  struct section_name_struct *aptr;
	  etree_type *align = 0;
	  etree_type *subalign = 0;
	  struct wildcard_list *tmp;

	  /* See if an alignment has been specified.  */
	  for (aptr = alignment; aptr; aptr = aptr->next)
	    if (strcmp (aptr->name, p->name) == 0)
	      align = aptr->align;

	  for (aptr = subalignment; aptr; aptr = aptr->next)
	    if (strcmp (aptr->name, p->name) == 0)
	      subalign = aptr->subalign;

	  if (base == 0)
	    base = p->vma ? p->vma : exp_nameop (NAME, ".");

	  lang_enter_output_section_statement (p->name, base,
					       p->ok_to_load ? 0 : noload_section,
					       align, subalign, NULL, 0);
	  base = 0;
	  tmp = xmalloc (sizeof *tmp);
	  tmp->next = NULL;
	  tmp->spec.name = p->name;
	  tmp->spec.exclude_name_list = NULL;
	  tmp->spec.sorted = none;
	  lang_add_wild (NULL, tmp, FALSE);

	  /* If there is an alias for this section, add it too.  */
	  for (aptr = alias; aptr; aptr = aptr->next)
	    if (strcmp (aptr->alias, p->name) == 0)
	      {
		tmp = xmalloc (sizeof *tmp);
		tmp->next = NULL;
		tmp->spec.name = aptr->name;
		tmp->spec.exclude_name_list = NULL;
		tmp->spec.sorted = none;
		lang_add_wild (NULL, tmp, FALSE);
	      }

	  lang_leave_output_section_statement (0, "*default*", NULL, NULL);

	  p = p->next;
	}
    }

  done_tree = 1;
}