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
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_FLT ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 

__attribute__((used)) static int
mips_type_needs_double_align (struct type *type)
{
  enum type_code typecode = TYPE_CODE (type);

  if (typecode == TYPE_CODE_FLT && TYPE_LENGTH (type) == 8)
    return 1;
  else if (typecode == TYPE_CODE_STRUCT)
    {
      if (TYPE_NFIELDS (type) < 1)
	return 0;
      return mips_type_needs_double_align (TYPE_FIELD_TYPE (type, 0));
    }
  else if (typecode == TYPE_CODE_UNION)
    {
      int i, n;

      n = TYPE_NFIELDS (type);
      for (i = 0; i < n; i++)
	if (mips_type_needs_double_align (TYPE_FIELD_TYPE (type, i)))
	  return 1;
      return 0;
    }
  return 0;
}