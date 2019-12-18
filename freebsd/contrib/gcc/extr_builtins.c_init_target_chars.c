#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ (* to_target_charset ) (char) ;} ;

/* Variables and functions */
 TYPE_1__ lang_hooks ; 
 scalar_t__ stub1 (char) ; 
 scalar_t__ stub2 (char) ; 
 scalar_t__ stub3 (char) ; 
 scalar_t__ stub4 (char) ; 
 scalar_t__ target_c ; 
 scalar_t__ target_newline ; 
 scalar_t__ target_percent ; 
 char* target_percent_c ; 
 char* target_percent_s ; 
 char* target_percent_s_newline ; 
 scalar_t__ target_s ; 

__attribute__((used)) static bool
init_target_chars (void)
{
  static bool init;
  if (!init)
    {
      target_newline = lang_hooks.to_target_charset ('\n');
      target_percent = lang_hooks.to_target_charset ('%');
      target_c = lang_hooks.to_target_charset ('c');
      target_s = lang_hooks.to_target_charset ('s');
      if (target_newline == 0 || target_percent == 0 || target_c == 0
	  || target_s == 0)
	return false;

      target_percent_c[0] = target_percent;
      target_percent_c[1] = target_c;
      target_percent_c[2] = '\0';

      target_percent_s[0] = target_percent;
      target_percent_s[1] = target_s;
      target_percent_s[2] = '\0';

      target_percent_s_newline[0] = target_percent;
      target_percent_s_newline[1] = target_s;
      target_percent_s_newline[2] = target_newline;
      target_percent_s_newline[3] = '\0';

      init = true;
    }
  return true;
}