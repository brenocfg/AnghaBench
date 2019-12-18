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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int GET_MODE_SIZE (int) ; 

int
thumb_legitimate_offset_p (enum machine_mode mode, HOST_WIDE_INT val)
{
  switch (GET_MODE_SIZE (mode))
    {
    case 1:
      return val >= 0 && val < 32;

    case 2:
      return val >= 0 && val < 64 && (val & 1) == 0;

    default:
      return (val >= 0
	      && (val + GET_MODE_SIZE (mode)) <= 128
	      && (val & 3) == 0);
    }
}