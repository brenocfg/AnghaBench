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
typedef  int CORE_ADDR ;

/* Variables and functions */
#define  BOUND_BY_REF_IN_REG 133 
#define  BOUND_BY_REF_ON_STACK 132 
#define  BOUND_BY_VALUE_IN_REG 131 
#define  BOUND_BY_VALUE_ON_STACK 130 
#define  BOUND_CANNOT_BE_DETERMINED 129 
 int BOUND_FETCH_ERROR ; 
 int BOUND_FETCH_OK ; 
#define  BOUND_SIMPLE 128 
 int DEFAULT_UPPER_BOUND ; 
 int TYPE_ARRAY_UPPER_BOUND_TYPE (struct type*) ; 
 int TYPE_ARRAY_UPPER_BOUND_VALUE (struct type*) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  f77_get_dynamic_lowerbound (struct type*,int*) ; 
 int get_frame_base (int /*<<< orphan*/ ) ; 
 int read_memory_integer (int,int) ; 
 int read_memory_typed_address (int,int /*<<< orphan*/ ) ; 

int
f77_get_dynamic_upperbound (struct type *type, int *upper_bound)
{
  CORE_ADDR current_frame_addr = 0;
  CORE_ADDR ptr_to_upper_bound;

  switch (TYPE_ARRAY_UPPER_BOUND_TYPE (type))
    {
    case BOUND_BY_VALUE_ON_STACK:
      current_frame_addr = get_frame_base (deprecated_selected_frame);
      if (current_frame_addr > 0)
	{
	  *upper_bound =
	    read_memory_integer (current_frame_addr +
				 TYPE_ARRAY_UPPER_BOUND_VALUE (type),
				 4);
	}
      else
	{
	  *upper_bound = DEFAULT_UPPER_BOUND;
	  return BOUND_FETCH_ERROR;
	}
      break;

    case BOUND_SIMPLE:
      *upper_bound = TYPE_ARRAY_UPPER_BOUND_VALUE (type);
      break;

    case BOUND_CANNOT_BE_DETERMINED:
      /* we have an assumed size array on our hands. Assume that 
         upper_bound == lower_bound so that we show at least 
         1 element.If the user wants to see more elements, let 
         him manually ask for 'em and we'll subscript the 
         array and show him */
      f77_get_dynamic_lowerbound (type, upper_bound);
      break;

    case BOUND_BY_REF_ON_STACK:
      current_frame_addr = get_frame_base (deprecated_selected_frame);
      if (current_frame_addr > 0)
	{
	  ptr_to_upper_bound =
	    read_memory_typed_address (current_frame_addr +
				       TYPE_ARRAY_UPPER_BOUND_VALUE (type),
				       builtin_type_void_data_ptr);
	  *upper_bound = read_memory_integer (ptr_to_upper_bound, 4);
	}
      else
	{
	  *upper_bound = DEFAULT_UPPER_BOUND;
	  return BOUND_FETCH_ERROR;
	}
      break;

    case BOUND_BY_REF_IN_REG:
    case BOUND_BY_VALUE_IN_REG:
    default:
      error ("??? unhandled dynamic array bound type ???");
      break;
    }
  return BOUND_FETCH_OK;
}