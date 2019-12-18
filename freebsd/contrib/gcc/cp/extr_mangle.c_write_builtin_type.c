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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  BOOLEAN_TYPE 131 
#define  INTEGER_TYPE 130 
#define  REAL_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FOR_JAVA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_IS_SIZETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  c_common_type_for_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_type_node ; 
 int /*<<< orphan*/  float_type_node ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char* integer_type_codes ; 
 int /*<<< orphan*/ * integer_types ; 
 size_t itk_none ; 
 int /*<<< orphan*/  java_double_type_node ; 
 int /*<<< orphan*/  java_float_type_node ; 
 int /*<<< orphan*/  long_double_type_node ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  wchar_type_node ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_java_integer_type_codes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char const*) ; 
 int /*<<< orphan*/  write_unsigned_number (scalar_t__) ; 

__attribute__((used)) static void
write_builtin_type (tree type)
{
  switch (TREE_CODE (type))
    {
    case VOID_TYPE:
      write_char ('v');
      break;

    case BOOLEAN_TYPE:
      write_char ('b');
      break;

    case INTEGER_TYPE:
      /* If this is size_t, get the underlying int type.  */
      if (TYPE_IS_SIZETYPE (type))
	type = TYPE_DOMAIN (type);

      /* TYPE may still be wchar_t, since that isn't in
	 integer_type_nodes.  */
      if (type == wchar_type_node)
	write_char ('w');
      else if (TYPE_FOR_JAVA (type))
	write_java_integer_type_codes (type);
      else
	{
	  size_t itk;
	  /* Assume TYPE is one of the shared integer type nodes.  Find
	     it in the array of these nodes.  */
	iagain:
	  for (itk = 0; itk < itk_none; ++itk)
	    if (type == integer_types[itk])
	      {
		/* Print the corresponding single-letter code.  */
		write_char (integer_type_codes[itk]);
		break;
	      }

	  if (itk == itk_none)
	    {
	      tree t = c_common_type_for_mode (TYPE_MODE (type),
					       TYPE_UNSIGNED (type));
	      if (type != t)
		{
		  type = t;
		  goto iagain;
		}

	      if (TYPE_PRECISION (type) == 128)
		write_char (TYPE_UNSIGNED (type) ? 'o' : 'n');
	      else
		{
		  /* Allow for cases where TYPE is not one of the shared
		     integer type nodes and write a "vendor extended builtin
		     type" with a name the form intN or uintN, respectively.
		     Situations like this can happen if you have an
		     __attribute__((__mode__(__SI__))) type and use exotic
		     switches like '-mint8' on AVR.  Of course, this is
		     undefined by the C++ ABI (and '-mint8' is not even
		     Standard C conforming), but when using such special
		     options you're pretty much in nowhere land anyway.  */
		  const char *prefix;
		  char prec[11];	/* up to ten digits for an unsigned */

		  prefix = TYPE_UNSIGNED (type) ? "uint" : "int";
		  sprintf (prec, "%u", (unsigned) TYPE_PRECISION (type));
		  write_char ('u');	/* "vendor extended builtin type" */
		  write_unsigned_number (strlen (prefix) + strlen (prec));
		  write_string (prefix);
		  write_string (prec);
		}
	    }
	}
      break;

    case REAL_TYPE:
      if (type == float_type_node
	  || type == java_float_type_node)
	write_char ('f');
      else if (type == double_type_node
	       || type == java_double_type_node)
	write_char ('d');
      else if (type == long_double_type_node)
	write_char ('e');
      else
	gcc_unreachable ();
      break;

    default:
      gcc_unreachable ();
    }
}