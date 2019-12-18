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
#define  ARRAY_TYPE 145 
#define  BOOLEAN_TYPE 144 
 int /*<<< orphan*/  CHAR_TYPE_SIZE ; 
#define  COMPLEX_TYPE 143 
#define  ENUMERAL_TYPE 142 
#define  ERROR_MARK 141 
 int /*<<< orphan*/  FLOAT_TYPE_SIZE ; 
#define  FUNCTION_TYPE 140 
#define  INTEGER_TYPE 139 
 int /*<<< orphan*/  INT_TYPE_SIZE ; 
#define  LANG_TYPE 138 
#define  METHOD_TYPE 137 
#define  OFFSET_TYPE 136 
#define  POINTER_TYPE 135 
#define  QUAL_UNION_TYPE 134 
#define  REAL_TYPE 133 
#define  RECORD_TYPE 132 
#define  REFERENCE_TYPE 131 
 int /*<<< orphan*/  SHORT_TYPE_SIZE ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

unsigned long
sparc_type_code (register tree type)
{
  register unsigned long qualifiers = 0;
  register unsigned shift;

  /* Only the first 30 bits of the qualifier are valid.  We must refrain from
     setting more, since some assemblers will give an error for this.  Also,
     we must be careful to avoid shifts of 32 bits or more to avoid getting
     unpredictable results.  */

  for (shift = 6; shift < 30; shift += 2, type = TREE_TYPE (type))
    {
      switch (TREE_CODE (type))
	{
	case ERROR_MARK:
	  return qualifiers;
  
	case ARRAY_TYPE:
	  qualifiers |= (3 << shift);
	  break;

	case FUNCTION_TYPE:
	case METHOD_TYPE:
	  qualifiers |= (2 << shift);
	  break;

	case POINTER_TYPE:
	case REFERENCE_TYPE:
	case OFFSET_TYPE:
	  qualifiers |= (1 << shift);
	  break;

	case RECORD_TYPE:
	  return (qualifiers | 8);

	case UNION_TYPE:
	case QUAL_UNION_TYPE:
	  return (qualifiers | 9);

	case ENUMERAL_TYPE:
	  return (qualifiers | 10);

	case VOID_TYPE:
	  return (qualifiers | 16);

	case INTEGER_TYPE:
	  /* If this is a range type, consider it to be the underlying
	     type.  */
	  if (TREE_TYPE (type) != 0)
	    break;

	  /* Carefully distinguish all the standard types of C,
	     without messing up if the language is not C.  We do this by
	     testing TYPE_PRECISION and TYPE_UNSIGNED.  The old code used to
	     look at both the names and the above fields, but that's redundant.
	     Any type whose size is between two C types will be considered
	     to be the wider of the two types.  Also, we do not have a
	     special code to use for "long long", so anything wider than
	     long is treated the same.  Note that we can't distinguish
	     between "int" and "long" in this code if they are the same
	     size, but that's fine, since neither can the assembler.  */

	  if (TYPE_PRECISION (type) <= CHAR_TYPE_SIZE)
	    return (qualifiers | (TYPE_UNSIGNED (type) ? 12 : 2));
  
	  else if (TYPE_PRECISION (type) <= SHORT_TYPE_SIZE)
	    return (qualifiers | (TYPE_UNSIGNED (type) ? 13 : 3));
  
	  else if (TYPE_PRECISION (type) <= INT_TYPE_SIZE)
	    return (qualifiers | (TYPE_UNSIGNED (type) ? 14 : 4));
  
	  else
	    return (qualifiers | (TYPE_UNSIGNED (type) ? 15 : 5));
  
	case REAL_TYPE:
	  /* If this is a range type, consider it to be the underlying
	     type.  */
	  if (TREE_TYPE (type) != 0)
	    break;

	  /* Carefully distinguish all the standard types of C,
	     without messing up if the language is not C.  */

	  if (TYPE_PRECISION (type) == FLOAT_TYPE_SIZE)
	    return (qualifiers | 6);

	  else 
	    return (qualifiers | 7);
  
	case COMPLEX_TYPE:	/* GNU Fortran COMPLEX type.  */
	  /* ??? We need to distinguish between double and float complex types,
	     but I don't know how yet because I can't reach this code from
	     existing front-ends.  */
	  return (qualifiers | 7);	/* Who knows? */

	case VECTOR_TYPE:
	case BOOLEAN_TYPE:	/* Boolean truth value type.  */
	case LANG_TYPE:		/* ? */
	  return qualifiers;
  
	default:
	  gcc_unreachable ();		/* Not a type! */
        }
    }

  return qualifiers;
}