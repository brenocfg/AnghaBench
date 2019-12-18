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

/* Variables and functions */
 scalar_t__ IDENTIFIER_CTOR_OR_DTOR_P (scalar_t__) ; 
 scalar_t__ IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ IDENTIFIER_TYPENAME_P (scalar_t__) ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ base_dtor_identifier ; 
 scalar_t__ complete_dtor_identifier ; 
 char* concat (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ constructor_name (scalar_t__) ; 
 scalar_t__ deleting_dtor_identifier ; 
 char* type_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
name_as_c_string (tree name, tree type, bool *free_p)
{
  char *pretty_name;

  /* Assume that we will not allocate memory.  */
  *free_p = false;
  /* Constructors and destructors are special.  */
  if (IDENTIFIER_CTOR_OR_DTOR_P (name))
    {
      pretty_name
	= (char *) IDENTIFIER_POINTER (constructor_name (type));
      /* For a destructor, add the '~'.  */
      if (name == complete_dtor_identifier
	  || name == base_dtor_identifier
	  || name == deleting_dtor_identifier)
	{
	  pretty_name = concat ("~", pretty_name, NULL);
	  /* Remember that we need to free the memory allocated.  */
	  *free_p = true;
	}
    }
  else if (IDENTIFIER_TYPENAME_P (name))
    {
      pretty_name = concat ("operator ",
			    type_as_string (TREE_TYPE (name),
					    TFF_PLAIN_IDENTIFIER),
			    NULL);
      /* Remember that we need to free the memory allocated.  */
      *free_p = true;
    }
  else
    pretty_name = (char *) IDENTIFIER_POINTER (name);

  return pretty_name;
}