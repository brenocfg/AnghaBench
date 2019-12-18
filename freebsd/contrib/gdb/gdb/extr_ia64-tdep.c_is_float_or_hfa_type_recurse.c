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
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 130 
#define  TYPE_CODE_FLT 129 
#define  TYPE_CODE_STRUCT 128 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_float_or_hfa_type_recurse (struct type *t, struct type **etp)
{
  switch (TYPE_CODE (t))
    {
    case TYPE_CODE_FLT:
      if (*etp)
	return TYPE_LENGTH (*etp) == TYPE_LENGTH (t);
      else
	{
	  *etp = t;
	  return 1;
	}
      break;
    case TYPE_CODE_ARRAY:
      return
	is_float_or_hfa_type_recurse (check_typedef (TYPE_TARGET_TYPE (t)),
				      etp);
      break;
    case TYPE_CODE_STRUCT:
      {
	int i;

	for (i = 0; i < TYPE_NFIELDS (t); i++)
	  if (!is_float_or_hfa_type_recurse
	      (check_typedef (TYPE_FIELD_TYPE (t, i)), etp))
	    return 0;
	return 1;
      }
      break;
    default:
      return 0;
      break;
    }
}