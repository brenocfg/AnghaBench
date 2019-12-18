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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_app_details (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raspicamcontrol_display_help () ; 
 int /*<<< orphan*/  raspicommonsettings_display_help () ; 
 int /*<<< orphan*/  raspipreview_display_help () ; 
 int /*<<< orphan*/  stdout ; 
 void stub1 (char*) ; 

void display_valid_parameters(char *name, void (*app_help)(char*))
{
   print_app_details(stdout);

   // This should be defined in the main app source code
   if (app_help)
      (*app_help)(name);

   // general settings
   raspicommonsettings_display_help();

   // Help for preview options
   raspipreview_display_help();

   // Now display any help information from the camcontrol code
   raspicamcontrol_display_help();

   fprintf(stdout, "\n");
}