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
struct value {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 int ada_vax_float_type_suffix (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct value* get_var_value (char*,int /*<<< orphan*/ ) ; 

struct value *
ada_vax_float_print_function (struct type *type)
{
  switch (ada_vax_float_type_suffix (type))
    {
    case 'F':
      return get_var_value ("DEBUG_STRING_F", 0);
    case 'D':
      return get_var_value ("DEBUG_STRING_D", 0);
    case 'G':
      return get_var_value ("DEBUG_STRING_G", 0);
    default:
      error ("invalid VAX floating-point type");
    }
}