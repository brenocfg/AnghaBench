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
typedef  void* tree ;
struct sra_elt {int is_group; int n_copies; struct sra_elt* children; struct sra_elt* sibling; struct sra_elt* groups; void* element; int /*<<< orphan*/  is_scalar; void* type; struct sra_elt* parent; } ;
typedef  enum insert_option { ____Placeholder_insert_option } insert_option ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_UID (void*) ; 
 int INSERT ; 
 scalar_t__ IS_ELEMENT_FOR_GROUP (void*) ; 
 int NO_INSERT ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (void*) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find_slot (int /*<<< orphan*/ ,struct sra_elt*,int) ; 
 int /*<<< orphan*/  is_sra_scalar_type (void*) ; 
 int /*<<< orphan*/  memset (struct sra_elt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  needs_copy_in ; 
 struct sra_elt* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sra_map ; 
 int /*<<< orphan*/  sra_obstack ; 

__attribute__((used)) static struct sra_elt *
lookup_element (struct sra_elt *parent, tree child, tree type,
		enum insert_option insert)
{
  struct sra_elt dummy;
  struct sra_elt **slot;
  struct sra_elt *elt;

  if (parent)
    dummy.parent = parent->is_group ? parent->parent : parent;
  else
    dummy.parent = NULL;
  dummy.element = child;

  slot = (struct sra_elt **) htab_find_slot (sra_map, &dummy, insert);
  if (!slot && insert == NO_INSERT)
    return NULL;

  elt = *slot;
  if (!elt && insert == INSERT)
    {
      *slot = elt = obstack_alloc (&sra_obstack, sizeof (*elt));
      memset (elt, 0, sizeof (*elt));

      elt->parent = parent;
      elt->element = child;
      elt->type = type;
      elt->is_scalar = is_sra_scalar_type (type);

      if (parent)
	{
	  if (IS_ELEMENT_FOR_GROUP (elt->element))
	    {
	      elt->is_group = true;
	      elt->sibling = parent->groups;
	      parent->groups = elt;
	    }
	  else
	    {
	      elt->sibling = parent->children;
	      parent->children = elt;
	    }
	}

      /* If this is a parameter, then if we want to scalarize, we have
	 one copy from the true function parameter.  Count it now.  */
      if (TREE_CODE (child) == PARM_DECL)
	{
	  elt->n_copies = 1;
	  bitmap_set_bit (needs_copy_in, DECL_UID (child));
	}
    }

  return elt;
}