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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int const TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 135 
#define  TYPE_CODE_ENUM 134 
#define  TYPE_CODE_FLT 133 
#define  TYPE_CODE_INT 132 
#define  TYPE_CODE_PTR 131 
#define  TYPE_CODE_RANGE 130 
 int const TYPE_CODE_REF ; 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 int const TYPE_CODE_VOID ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  ada_is_array_descriptor (struct type*) ; 

__attribute__((used)) static int
ada_type_match (struct type *ftype, struct type *atype, int may_deref)
{
  CHECK_TYPEDEF (ftype);
  CHECK_TYPEDEF (atype);

  if (TYPE_CODE (ftype) == TYPE_CODE_REF)
    ftype = TYPE_TARGET_TYPE (ftype);
  if (TYPE_CODE (atype) == TYPE_CODE_REF)
    atype = TYPE_TARGET_TYPE (atype);

  if (TYPE_CODE (ftype) == TYPE_CODE_VOID
      || TYPE_CODE (atype) == TYPE_CODE_VOID)
    return 1;

  switch (TYPE_CODE (ftype))
    {
    default:
      return 1;
    case TYPE_CODE_PTR:
      if (TYPE_CODE (atype) == TYPE_CODE_PTR)
	return ada_type_match (TYPE_TARGET_TYPE (ftype),
			       TYPE_TARGET_TYPE (atype), 0);
      else
	return (may_deref &&
		ada_type_match (TYPE_TARGET_TYPE (ftype), atype, 0));
    case TYPE_CODE_INT:
    case TYPE_CODE_ENUM:
    case TYPE_CODE_RANGE:
      switch (TYPE_CODE (atype))
	{
	case TYPE_CODE_INT:
	case TYPE_CODE_ENUM:
	case TYPE_CODE_RANGE:
	  return 1;
	default:
	  return 0;
	}

    case TYPE_CODE_ARRAY:
      return (TYPE_CODE (atype) == TYPE_CODE_ARRAY
	      || ada_is_array_descriptor (atype));

    case TYPE_CODE_STRUCT:
      if (ada_is_array_descriptor (ftype))
	return (TYPE_CODE (atype) == TYPE_CODE_ARRAY
		|| ada_is_array_descriptor (atype));
      else
	return (TYPE_CODE (atype) == TYPE_CODE_STRUCT
		&& !ada_is_array_descriptor (atype));

    case TYPE_CODE_UNION:
    case TYPE_CODE_FLT:
      return (TYPE_CODE (atype) == TYPE_CODE (ftype));
    }
}