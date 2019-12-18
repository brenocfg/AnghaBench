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
 scalar_t__ case_mode ; 
 scalar_t__ case_mode_auto ; 
 int /*<<< orphan*/  case_sensitive ; 
#define  case_sensitive_off 129 
#define  case_sensitive_on 128 
 int case_sensitivity ; 
 int /*<<< orphan*/  concat (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_case_str (void)
{
   char *tmp = NULL, *prefix = "";

   if (case_mode==case_mode_auto)
      prefix = "auto; currently ";

   switch (case_sensitivity)
   {
   case case_sensitive_on:
     tmp = "on";
     break;
   case case_sensitive_off:
     tmp = "off";
     break;
   default:
     error ("Unrecognized case-sensitive setting.");
   }

   xfree (case_sensitive);
   case_sensitive = concat (prefix, tmp, NULL);
}