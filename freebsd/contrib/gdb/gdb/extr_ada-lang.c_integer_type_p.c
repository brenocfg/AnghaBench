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
#define  TYPE_CODE_INT 129 
#define  TYPE_CODE_RANGE 128 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 

__attribute__((used)) static int
integer_type_p (struct type *type)
{
  if (type == NULL)
    return 0;
  else
    {
      switch (TYPE_CODE (type))
	{
	case TYPE_CODE_INT:
	  return 1;
	case TYPE_CODE_RANGE:
	  return (type == TYPE_TARGET_TYPE (type)
		  || integer_type_p (TYPE_TARGET_TYPE (type)));
	default:
	  return 0;
	}
    }
}