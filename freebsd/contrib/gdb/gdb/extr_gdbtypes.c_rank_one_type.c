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
struct type {int dummy; } ;

/* Variables and functions */
 int BASE_CONVERSION_BADNESS ; 
 int BOOLEAN_CONVERSION_BADNESS ; 
 int FLOAT_CONVERSION_BADNESS ; 
 int FLOAT_PROMOTION_BADNESS ; 
 int INCOMPATIBLE_TYPE_BADNESS ; 
 int INTEGER_CONVERSION_BADNESS ; 
 int INTEGER_PROMOTION_BADNESS ; 
 int INT_FLOAT_CONVERSION_BADNESS ; 
 int NS_POINTER_CONVERSION_BADNESS ; 
 int POINTER_CONVERSION_BADNESS ; 
 int REFERENCE_CONVERSION_BADNESS ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 144 
#define  TYPE_CODE_BOOL 143 
#define  TYPE_CODE_CHAR 142 
#define  TYPE_CODE_COMPLEX 141 
#define  TYPE_CODE_ENUM 140 
#define  TYPE_CODE_FLT 139 
#define  TYPE_CODE_FUNC 138 
#define  TYPE_CODE_INT 137 
#define  TYPE_CODE_MEMBER 136 
#define  TYPE_CODE_METHOD 135 
#define  TYPE_CODE_PTR 134 
#define  TYPE_CODE_RANGE 133 
#define  TYPE_CODE_REF 132 
#define  TYPE_CODE_SET 131 
#define  TYPE_CODE_STRUCT 130 
 int TYPE_CODE_TYPEDEF ; 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 struct type* TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 char* TYPE_NAME (struct type*) ; 
 int /*<<< orphan*/  TYPE_NOSIGN (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 
 int VOID_PTR_CONVERSION_BADNESS ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*,char*,int,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  integer_types_same_name_p (char*,char*) ; 
 int /*<<< orphan*/  is_ancestor (struct type*,struct type*) ; 
 scalar_t__ overload_debug ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
rank_one_type (struct type *parm, struct type *arg)
{
  /* Identical type pointers */
  /* However, this still doesn't catch all cases of same type for arg
   * and param. The reason is that builtin types are different from
   * the same ones constructed from the object. */
  if (parm == arg)
    return 0;

  /* Resolve typedefs */
  if (TYPE_CODE (parm) == TYPE_CODE_TYPEDEF)
    parm = check_typedef (parm);
  if (TYPE_CODE (arg) == TYPE_CODE_TYPEDEF)
    arg = check_typedef (arg);

  /*
     Well, damnit, if the names are exactly the same,
     i'll say they are exactly the same. This happens when we generate
     method stubs. The types won't point to the same address, but they
     really are the same.
  */

  if (TYPE_NAME (parm) && TYPE_NAME (arg) &&
      !strcmp (TYPE_NAME (parm), TYPE_NAME (arg)))
      return 0;

  /* Check if identical after resolving typedefs */
  if (parm == arg)
    return 0;

  /* See through references, since we can almost make non-references
     references. */
  if (TYPE_CODE (arg) == TYPE_CODE_REF)
    return (rank_one_type (parm, TYPE_TARGET_TYPE (arg))
	    + REFERENCE_CONVERSION_BADNESS);
  if (TYPE_CODE (parm) == TYPE_CODE_REF)
    return (rank_one_type (TYPE_TARGET_TYPE (parm), arg)
	    + REFERENCE_CONVERSION_BADNESS);
  if (overload_debug)
  /* Debugging only. */
    fprintf_filtered (gdb_stderr,"------ Arg is %s [%d], parm is %s [%d]\n",
        TYPE_NAME (arg), TYPE_CODE (arg), TYPE_NAME (parm), TYPE_CODE (parm));

  /* x -> y means arg of type x being supplied for parameter of type y */

  switch (TYPE_CODE (parm))
    {
    case TYPE_CODE_PTR:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_PTR:
	  if (TYPE_CODE (TYPE_TARGET_TYPE (parm)) == TYPE_CODE_VOID)
	    return VOID_PTR_CONVERSION_BADNESS;
	  else
	    return rank_one_type (TYPE_TARGET_TYPE (parm), TYPE_TARGET_TYPE (arg));
	case TYPE_CODE_ARRAY:
	  return rank_one_type (TYPE_TARGET_TYPE (parm), TYPE_TARGET_TYPE (arg));
	case TYPE_CODE_FUNC:
	  return rank_one_type (TYPE_TARGET_TYPE (parm), arg);
	case TYPE_CODE_INT:
	case TYPE_CODE_ENUM:
	case TYPE_CODE_CHAR:
	case TYPE_CODE_RANGE:
	case TYPE_CODE_BOOL:
	  return POINTER_CONVERSION_BADNESS;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
    case TYPE_CODE_ARRAY:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_PTR:
	case TYPE_CODE_ARRAY:
	  return rank_one_type (TYPE_TARGET_TYPE (parm), TYPE_TARGET_TYPE (arg));
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
    case TYPE_CODE_FUNC:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_PTR:	/* funcptr -> func */
	  return rank_one_type (parm, TYPE_TARGET_TYPE (arg));
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
    case TYPE_CODE_INT:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_INT:
	  if (TYPE_LENGTH (arg) == TYPE_LENGTH (parm))
	    {
	      /* Deal with signed, unsigned, and plain chars and
	         signed and unsigned ints */
	      if (TYPE_NOSIGN (parm))
		{
		  /* This case only for character types */
		  if (TYPE_NOSIGN (arg))	/* plain char -> plain char */
		    return 0;
		  else
		    return INTEGER_CONVERSION_BADNESS;	/* signed/unsigned char -> plain char */
		}
	      else if (TYPE_UNSIGNED (parm))
		{
		  if (TYPE_UNSIGNED (arg))
		    {
		      /* unsigned int -> unsigned int, or unsigned long -> unsigned long */
		      if (integer_types_same_name_p (TYPE_NAME (parm), TYPE_NAME (arg)))
			return 0;
		      else if (integer_types_same_name_p (TYPE_NAME (arg), "int")
			       && integer_types_same_name_p (TYPE_NAME (parm), "long"))
			return INTEGER_PROMOTION_BADNESS;	/* unsigned int -> unsigned long */
		      else
			return INTEGER_CONVERSION_BADNESS;	/* unsigned long -> unsigned int */
		    }
		  else
		    {
		      if (integer_types_same_name_p (TYPE_NAME (arg), "long")
			  && integer_types_same_name_p (TYPE_NAME (parm), "int"))
			return INTEGER_CONVERSION_BADNESS;	/* signed long -> unsigned int */
		      else
			return INTEGER_CONVERSION_BADNESS;	/* signed int/long -> unsigned int/long */
		    }
		}
	      else if (!TYPE_NOSIGN (arg) && !TYPE_UNSIGNED (arg))
		{
		  if (integer_types_same_name_p (TYPE_NAME (parm), TYPE_NAME (arg)))
		    return 0;
		  else if (integer_types_same_name_p (TYPE_NAME (arg), "int")
			   && integer_types_same_name_p (TYPE_NAME (parm), "long"))
		    return INTEGER_PROMOTION_BADNESS;
		  else
		    return INTEGER_CONVERSION_BADNESS;
		}
	      else
		return INTEGER_CONVERSION_BADNESS;
	    }
	  else if (TYPE_LENGTH (arg) < TYPE_LENGTH (parm))
	    return INTEGER_PROMOTION_BADNESS;
	  else
	    return INTEGER_CONVERSION_BADNESS;
	case TYPE_CODE_ENUM:
	case TYPE_CODE_CHAR:
	case TYPE_CODE_RANGE:
	case TYPE_CODE_BOOL:
	  return INTEGER_PROMOTION_BADNESS;
	case TYPE_CODE_FLT:
	  return INT_FLOAT_CONVERSION_BADNESS;
	case TYPE_CODE_PTR:
	  return NS_POINTER_CONVERSION_BADNESS;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_ENUM:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_INT:
	case TYPE_CODE_CHAR:
	case TYPE_CODE_RANGE:
	case TYPE_CODE_BOOL:
	case TYPE_CODE_ENUM:
	  return INTEGER_CONVERSION_BADNESS;
	case TYPE_CODE_FLT:
	  return INT_FLOAT_CONVERSION_BADNESS;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_CHAR:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_RANGE:
	case TYPE_CODE_BOOL:
	case TYPE_CODE_ENUM:
	  return INTEGER_CONVERSION_BADNESS;
	case TYPE_CODE_FLT:
	  return INT_FLOAT_CONVERSION_BADNESS;
	case TYPE_CODE_INT:
	  if (TYPE_LENGTH (arg) > TYPE_LENGTH (parm))
	    return INTEGER_CONVERSION_BADNESS;
	  else if (TYPE_LENGTH (arg) < TYPE_LENGTH (parm))
	    return INTEGER_PROMOTION_BADNESS;
	  /* >>> !! else fall through !! <<< */
	case TYPE_CODE_CHAR:
	  /* Deal with signed, unsigned, and plain chars for C++
	     and with int cases falling through from previous case */
	  if (TYPE_NOSIGN (parm))
	    {
	      if (TYPE_NOSIGN (arg))
		return 0;
	      else
		return INTEGER_CONVERSION_BADNESS;
	    }
	  else if (TYPE_UNSIGNED (parm))
	    {
	      if (TYPE_UNSIGNED (arg))
		return 0;
	      else
		return INTEGER_PROMOTION_BADNESS;
	    }
	  else if (!TYPE_NOSIGN (arg) && !TYPE_UNSIGNED (arg))
	    return 0;
	  else
	    return INTEGER_CONVERSION_BADNESS;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_RANGE:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_INT:
	case TYPE_CODE_CHAR:
	case TYPE_CODE_RANGE:
	case TYPE_CODE_BOOL:
	case TYPE_CODE_ENUM:
	  return INTEGER_CONVERSION_BADNESS;
	case TYPE_CODE_FLT:
	  return INT_FLOAT_CONVERSION_BADNESS;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_BOOL:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_INT:
	case TYPE_CODE_CHAR:
	case TYPE_CODE_RANGE:
	case TYPE_CODE_ENUM:
	case TYPE_CODE_FLT:
	case TYPE_CODE_PTR:
	  return BOOLEAN_CONVERSION_BADNESS;
	case TYPE_CODE_BOOL:
	  return 0;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_FLT:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_FLT:
	  if (TYPE_LENGTH (arg) < TYPE_LENGTH (parm))
	    return FLOAT_PROMOTION_BADNESS;
	  else if (TYPE_LENGTH (arg) == TYPE_LENGTH (parm))
	    return 0;
	  else
	    return FLOAT_CONVERSION_BADNESS;
	case TYPE_CODE_INT:
	case TYPE_CODE_BOOL:
	case TYPE_CODE_ENUM:
	case TYPE_CODE_RANGE:
	case TYPE_CODE_CHAR:
	  return INT_FLOAT_CONVERSION_BADNESS;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_COMPLEX:
      switch (TYPE_CODE (arg))
	{			/* Strictly not needed for C++, but... */
	case TYPE_CODE_FLT:
	  return FLOAT_PROMOTION_BADNESS;
	case TYPE_CODE_COMPLEX:
	  return 0;
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_STRUCT:
      /* currently same as TYPE_CODE_CLASS */
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_STRUCT:
	  /* Check for derivation */
	  if (is_ancestor (parm, arg))
	    return BASE_CONVERSION_BADNESS;
	  /* else fall through */
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_UNION:
      switch (TYPE_CODE (arg))
	{
	case TYPE_CODE_UNION:
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_MEMBER:
      switch (TYPE_CODE (arg))
	{
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_METHOD:
      switch (TYPE_CODE (arg))
	{

	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_REF:
      switch (TYPE_CODE (arg))
	{

	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}

      break;
    case TYPE_CODE_SET:
      switch (TYPE_CODE (arg))
	{
	  /* Not in C++ */
	case TYPE_CODE_SET:
	  return rank_one_type (TYPE_FIELD_TYPE (parm, 0), TYPE_FIELD_TYPE (arg, 0));
	default:
	  return INCOMPATIBLE_TYPE_BADNESS;
	}
      break;
    case TYPE_CODE_VOID:
    default:
      return INCOMPATIBLE_TYPE_BADNESS;
    }				/* switch (TYPE_CODE (arg)) */
}