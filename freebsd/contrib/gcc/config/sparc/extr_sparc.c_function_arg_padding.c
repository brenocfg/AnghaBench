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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum direction { ____Placeholder_direction } direction ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 int DEFAULT_FUNCTION_ARG_PADDING (int,scalar_t__) ; 
 scalar_t__ TARGET_ARCH64 ; 
 int upward ; 

enum direction
function_arg_padding (enum machine_mode mode, tree type)
{
  if (TARGET_ARCH64 && type != 0 && AGGREGATE_TYPE_P (type))
    return upward;

  /* Fall back to the default.  */
  return DEFAULT_FUNCTION_ARG_PADDING (mode, type);
}