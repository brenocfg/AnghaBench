#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* mode; } ;
struct TYPE_7__ {char* mode; } ;
struct TYPE_6__ {char* mode; } ;
struct TYPE_5__ {char* mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* intra_refresh_map ; 
 int intra_refresh_map_size ; 
 TYPE_3__* level_map ; 
 int level_map_size ; 
 TYPE_2__* profile_map ; 
 int profile_map_size ; 
 int /*<<< orphan*/  raspicli_display_help (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* raw_output_fmt_map ; 
 int raw_output_fmt_map_size ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void application_help_message(char *app_name)
{
   int i;

   fprintf(stdout, "Display camera output to display, and optionally saves an H264 capture at requested bitrate\n\n");
   fprintf(stdout, "\nusage: %s [options]\n\n", app_name);

   fprintf(stdout, "Image parameter commands\n\n");

   raspicli_display_help(cmdline_commands, cmdline_commands_size);

   // Profile options
   fprintf(stdout, "\n\nH264 Profile options :\n%s", profile_map[0].mode );

   for (i=1; i<profile_map_size; i++)
   {
      fprintf(stdout, ",%s", profile_map[i].mode);
   }

   // Level options
   fprintf(stdout, "\n\nH264 Level options :\n%s", level_map[0].mode );

   for (i=1; i<level_map_size; i++)
   {
      fprintf(stdout, ",%s", level_map[i].mode);
   }

   // Intra refresh options
   fprintf(stdout, "\n\nH264 Intra refresh options :\n%s", intra_refresh_map[0].mode );

   for (i=1; i<intra_refresh_map_size; i++)
   {
      fprintf(stdout, ",%s", intra_refresh_map[i].mode);
   }

   // Raw output format options
   fprintf(stdout, "\n\nRaw output format options :\n%s", raw_output_fmt_map[0].mode );

   for (i=1; i<raw_output_fmt_map_size; i++)
   {
      fprintf(stdout, ",%s", raw_output_fmt_map[i].mode);
   }

   fprintf(stdout, "\n\n");

   fprintf(stdout, "Raspivid allows output to a remote IPv4 host e.g. -o tcp://192.168.1.2:1234"
           "or -o udp://192.168.1.2:1234\n"
           "To listen on a TCP port (IPv4) and wait for an incoming connection use the -l option\n"
           "e.g. raspivid -l -o tcp://0.0.0.0:3333 -> bind to all network interfaces,\n"
           "raspivid -l -o tcp://192.168.1.1:3333 -> bind to a certain local IPv4 port\n");

   return;
}