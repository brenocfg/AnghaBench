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
struct cl_option {int var_type; int var_value; scalar_t__ flag_var; } ;

/* Variables and functions */
#define  CLVC_BIT_CLEAR 132 
#define  CLVC_BIT_SET 131 
#define  CLVC_BOOLEAN 130 
#define  CLVC_EQUAL 129 
#define  CLVC_STRING 128 
 struct cl_option* cl_options ; 

int
option_enabled (int opt_idx)
{
  const struct cl_option *option = &(cl_options[opt_idx]);
  if (option->flag_var)
    switch (option->var_type)
      {
      case CLVC_BOOLEAN:
	return *(int *) option->flag_var != 0;

      case CLVC_EQUAL:
	return *(int *) option->flag_var == option->var_value;

      case CLVC_BIT_CLEAR:
	return (*(int *) option->flag_var & option->var_value) == 0;

      case CLVC_BIT_SET:
	return (*(int *) option->flag_var & option->var_value) != 0;

      case CLVC_STRING:
	break;
      }
  return -1;
}