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
typedef  scalar_t__ tree ;
struct sra_elt {scalar_t__ type; scalar_t__ element; struct sra_elt* parent; } ;

/* Variables and functions */
 scalar_t__ COMPLEX_TYPE ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 int DECL_UID (scalar_t__) ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 int IDENTIFIER_LENGTH (scalar_t__) ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sra_obstack ; 
 int strlen (char*) ; 

__attribute__((used)) static void
build_element_name_1 (struct sra_elt *elt)
{
  tree t;
  char buffer[32];

  if (elt->parent)
    {
      build_element_name_1 (elt->parent);
      obstack_1grow (&sra_obstack, '$');

      if (TREE_CODE (elt->parent->type) == COMPLEX_TYPE)
	{
	  if (elt->element == integer_zero_node)
	    obstack_grow (&sra_obstack, "real", 4);
	  else
	    obstack_grow (&sra_obstack, "imag", 4);
	  return;
	}
    }

  t = elt->element;
  if (TREE_CODE (t) == INTEGER_CST)
    {
      /* ??? Eh.  Don't bother doing double-wide printing.  */
      sprintf (buffer, HOST_WIDE_INT_PRINT_DEC, TREE_INT_CST_LOW (t));
      obstack_grow (&sra_obstack, buffer, strlen (buffer));
    }
  else
    {
      tree name = DECL_NAME (t);
      if (name)
	obstack_grow (&sra_obstack, IDENTIFIER_POINTER (name),
		      IDENTIFIER_LENGTH (name));
      else
	{
	  sprintf (buffer, "D%u", DECL_UID (t));
	  obstack_grow (&sra_obstack, buffer, strlen (buffer));
	}
    }
}