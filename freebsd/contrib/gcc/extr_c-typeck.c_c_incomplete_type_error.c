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
#define  ARRAY_TYPE 132 
#define  ENUMERAL_TYPE 131 
 int ERROR_MARK ; 
 int IDENTIFIER_NODE ; 
 int PARM_DECL ; 
#define  RECORD_TYPE 130 
 int TREE_CODE (char*) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (scalar_t__) ; 
 int /*<<< orphan*/ * TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 char* TYPE_NAME (scalar_t__) ; 
#define  UNION_TYPE 129 
 int VAR_DECL ; 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

void
c_incomplete_type_error (tree value, tree type)
{
  const char *type_code_string;

  /* Avoid duplicate error message.  */
  if (TREE_CODE (type) == ERROR_MARK)
    return;

  if (value != 0 && (TREE_CODE (value) == VAR_DECL
		     || TREE_CODE (value) == PARM_DECL))
    error ("%qD has an incomplete type", value);
  else
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      switch (TREE_CODE (type))
	{
	case RECORD_TYPE:
	  type_code_string = "struct";
	  break;

	case UNION_TYPE:
	  type_code_string = "union";
	  break;

	case ENUMERAL_TYPE:
	  type_code_string = "enum";
	  break;

	case VOID_TYPE:
	  error ("invalid use of void expression");
	  return;

	case ARRAY_TYPE:
	  if (TYPE_DOMAIN (type))
	    {
	      if (TYPE_MAX_VALUE (TYPE_DOMAIN (type)) == NULL)
		{
		  error ("invalid use of flexible array member");
		  return;
		}
	      type = TREE_TYPE (type);
	      goto retry;
	    }
	  error ("invalid use of array with unspecified bounds");
	  return;

	default:
	  gcc_unreachable ();
	}

      if (TREE_CODE (TYPE_NAME (type)) == IDENTIFIER_NODE)
	error ("invalid use of undefined type %<%s %E%>",
	       type_code_string, TYPE_NAME (type));
      else
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error ("invalid use of incomplete typedef %qD", TYPE_NAME (type));
    }
}