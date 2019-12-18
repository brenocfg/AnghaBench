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
typedef  enum type_class { ____Placeholder_type_class } type_class ;

/* Variables and functions */
#define  ARRAY_TYPE 143 
#define  BOOLEAN_TYPE 142 
#define  COMPLEX_TYPE 141 
#define  ENUMERAL_TYPE 140 
#define  FUNCTION_TYPE 139 
#define  INTEGER_TYPE 138 
#define  LANG_TYPE 137 
#define  METHOD_TYPE 136 
#define  OFFSET_TYPE 135 
#define  POINTER_TYPE 134 
#define  QUAL_UNION_TYPE 133 
#define  REAL_TYPE 132 
#define  RECORD_TYPE 131 
#define  REFERENCE_TYPE 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_STRING_FLAG (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 129 
#define  VOID_TYPE 128 
 int array_type_class ; 
 int boolean_type_class ; 
 int complex_type_class ; 
 int enumeral_type_class ; 
 int function_type_class ; 
 int integer_type_class ; 
 int lang_type_class ; 
 int method_type_class ; 
 int no_type_class ; 
 int offset_type_class ; 
 int pointer_type_class ; 
 int real_type_class ; 
 int record_type_class ; 
 int reference_type_class ; 
 int string_type_class ; 
 int union_type_class ; 
 int void_type_class ; 

__attribute__((used)) static enum type_class
type_to_class (tree type)
{
  switch (TREE_CODE (type))
    {
    case VOID_TYPE:	   return void_type_class;
    case INTEGER_TYPE:	   return integer_type_class;
    case ENUMERAL_TYPE:	   return enumeral_type_class;
    case BOOLEAN_TYPE:	   return boolean_type_class;
    case POINTER_TYPE:	   return pointer_type_class;
    case REFERENCE_TYPE:   return reference_type_class;
    case OFFSET_TYPE:	   return offset_type_class;
    case REAL_TYPE:	   return real_type_class;
    case COMPLEX_TYPE:	   return complex_type_class;
    case FUNCTION_TYPE:	   return function_type_class;
    case METHOD_TYPE:	   return method_type_class;
    case RECORD_TYPE:	   return record_type_class;
    case UNION_TYPE:
    case QUAL_UNION_TYPE:  return union_type_class;
    case ARRAY_TYPE:	   return (TYPE_STRING_FLAG (type)
				   ? string_type_class : array_type_class);
    case LANG_TYPE:	   return lang_type_class;
    default:		   return no_type_class;
    }
}