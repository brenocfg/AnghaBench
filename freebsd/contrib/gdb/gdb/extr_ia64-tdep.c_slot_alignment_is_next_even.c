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
#define  TYPE_CODE_ARRAY 131 
#define  TYPE_CODE_FLT 130 
#define  TYPE_CODE_INT 129 
#define  TYPE_CODE_STRUCT 128 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
slot_alignment_is_next_even (struct type *t)
{
  switch (TYPE_CODE (t))
    {
    case TYPE_CODE_INT:
    case TYPE_CODE_FLT:
      if (TYPE_LENGTH (t) > 8)
	return 1;
      else
	return 0;
    case TYPE_CODE_ARRAY:
      return
	slot_alignment_is_next_even (check_typedef (TYPE_TARGET_TYPE (t)));
    case TYPE_CODE_STRUCT:
      {
	int i;

	for (i = 0; i < TYPE_NFIELDS (t); i++)
	  if (slot_alignment_is_next_even
	      (check_typedef (TYPE_FIELD_TYPE (t, i))))
	    return 1;
	return 0;
      }
    default:
      return 0;
    }
}