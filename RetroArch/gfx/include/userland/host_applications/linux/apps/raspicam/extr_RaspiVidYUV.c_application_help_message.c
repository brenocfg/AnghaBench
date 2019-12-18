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
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  raspicli_display_help (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void application_help_message(char *app_name)
{
   fprintf(stdout, "Display camera output to display, and optionally saves an uncompressed YUV420 or RGB file \n\n");
   fprintf(stdout, "NOTE: High resolutions and/or frame rates may exceed the bandwidth of the system due\n");
   fprintf(stdout, "to the large amounts of data being moved to the SD card. This will result in undefined\n");
   fprintf(stdout, "results in the subsequent file.\n");
   fprintf(stdout, "The single raw file produced contains all the images. Each image in the files will be of size\n");
   fprintf(stdout, "width*height*1.5 for YUV or width*height*3 for RGB, unless width and/or height are not divisible by 16.");
   fprintf(stdout, "Use the image size displayed during the run (in verbose mode) for an accurate value\n");

   fprintf(stdout, "The Linux split command can be used to split up the file to individual frames\n");

   fprintf(stdout, "\nusage: %s [options]\n\n", app_name);

   fprintf(stdout, "Image parameter commands\n\n");

   raspicli_display_help(cmdline_commands, cmdline_commands_size);

   fprintf(stdout, "\n");

   return;
}