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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int flag_apple_kext ; 
 scalar_t__ flag_exceptions ; 
 scalar_t__ flag_mkernel ; 
 int flag_no_common ; 
 scalar_t__ flag_non_call_exceptions ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
darwin_override_options (void)
{
  if (flag_apple_kext && strcmp (lang_hooks.name, "GNU C++") != 0)
    {
      warning (0, "command line option %<-fapple-kext%> is only valid for C++");
      flag_apple_kext = 0;
    }
  if (flag_mkernel || flag_apple_kext)
    {
      /* -mkernel implies -fapple-kext for C++ */
      if (strcmp (lang_hooks.name, "GNU C++") == 0)
	flag_apple_kext = 1;

      flag_no_common = 1;

      /* No EH in kexts.  */
      flag_exceptions = 0;
      /* No -fnon-call-exceptions data in kexts.  */
      flag_non_call_exceptions = 0;
    }
}