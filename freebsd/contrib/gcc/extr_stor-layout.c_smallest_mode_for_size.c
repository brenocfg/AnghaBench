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
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_CLASS_NARROWEST_MODE (int) ; 
 unsigned int GET_MODE_PRECISION (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

enum machine_mode
smallest_mode_for_size (unsigned int size, enum mode_class class)
{
  enum machine_mode mode;

  /* Get the first mode which has at least this size, in the
     specified class.  */
  for (mode = GET_CLASS_NARROWEST_MODE (class); mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if (GET_MODE_PRECISION (mode) >= size)
      return mode;

  gcc_unreachable ();
}