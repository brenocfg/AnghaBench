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

/* Variables and functions */
 int warn_format ; 
 int warn_format_extra_args ; 
 int warn_format_nonliteral ; 
 int warn_format_security ; 
 int warn_format_y2k ; 
 int warn_format_zero_length ; 
 int warn_nonnull ; 

void
set_Wformat (int setting)
{
  warn_format = setting;
  warn_format_extra_args = setting;
  warn_format_zero_length = setting;
  if (setting != 1)
    {
      warn_format_nonliteral = setting;
      warn_format_security = setting;
      warn_format_y2k = setting;
    }
  /* Make sure not to disable -Wnonnull if -Wformat=0 is specified.  */
  if (setting)
    warn_nonnull = setting;
}