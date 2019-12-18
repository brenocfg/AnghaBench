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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ INTEGRAL_OR_ENUMERATION_TYPE_P (scalar_t__) ; 
 scalar_t__ dependent_type_p (scalar_t__) ; 
 scalar_t__ error_mark_node ; 

bool
cast_valid_in_integral_constant_expression_p (tree type)
{
  return (INTEGRAL_OR_ENUMERATION_TYPE_P (type)
	  || dependent_type_p (type)
	  || type == error_mark_node);
}