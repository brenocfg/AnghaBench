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
typedef  int stepping_mode_t ;

/* Variables and functions */
#define  DO_CONTINUE 130 
#define  DO_DEFAULT 129 
#define  DO_STEP 128 

__attribute__((used)) static char *
get_printable_name_of_stepping_mode (stepping_mode_t mode)
{
  switch (mode)
    {
    case DO_DEFAULT:
      return "DO_DEFAULT";
    case DO_STEP:
      return "DO_STEP";
    case DO_CONTINUE:
      return "DO_CONTINUE";
    default:
      return "?unknown mode?";
    }
}