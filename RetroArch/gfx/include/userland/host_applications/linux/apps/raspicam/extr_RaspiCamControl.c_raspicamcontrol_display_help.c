#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* mode; } ;
struct TYPE_11__ {char* mode; } ;
struct TYPE_10__ {char* mode; } ;
struct TYPE_9__ {char* mode; } ;
struct TYPE_8__ {char* mode; } ;
struct TYPE_7__ {char* mode; } ;

/* Variables and functions */
 TYPE_6__* awb_map ; 
 int awb_map_size ; 
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 TYPE_5__* drc_mode_map ; 
 int drc_mode_map_size ; 
 TYPE_4__* exposure_map ; 
 int exposure_map_size ; 
 TYPE_3__* flicker_avoid_map ; 
 int flicker_avoid_map_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* imagefx_map ; 
 int imagefx_map_size ; 
 TYPE_1__* metering_mode_map ; 
 int metering_mode_map_size ; 
 int /*<<< orphan*/  raspicli_display_help (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void raspicamcontrol_display_help()
{
   int i;

   fprintf(stdout, "\nImage parameter commands\n\n");

   raspicli_display_help(cmdline_commands, cmdline_commands_size);

   fprintf(stdout, "\n\nNotes\n\nExposure mode options :\n%s", exposure_map[0].mode );

   for (i=1; i<exposure_map_size; i++)
   {
      fprintf(stdout, ",%s", exposure_map[i].mode);
   }

   fprintf(stdout, "\n\nFlicker avoid mode options :\n%s", flicker_avoid_map[0].mode );

   for (i=1; i<flicker_avoid_map_size; i++)
   {
      fprintf(stdout, ",%s", flicker_avoid_map[i].mode);
   }

   fprintf(stdout, "\n\nAWB mode options :\n%s", awb_map[0].mode );

   for (i=1; i<awb_map_size; i++)
   {
      fprintf(stdout, ",%s", awb_map[i].mode);
   }

   fprintf(stdout, "\n\nImage Effect mode options :\n%s", imagefx_map[0].mode );

   for (i=1; i<imagefx_map_size; i++)
   {
      fprintf(stdout, ",%s", imagefx_map[i].mode);
   }

   fprintf(stdout, "\n\nMetering Mode options :\n%s", metering_mode_map[0].mode );

   for (i=1; i<metering_mode_map_size; i++)
   {
      fprintf(stdout, ",%s", metering_mode_map[i].mode);
   }

   fprintf(stdout, "\n\nDynamic Range Compression (DRC) options :\n%s", drc_mode_map[0].mode );

   for (i=1; i<drc_mode_map_size; i++)
   {
      fprintf(stdout, ",%s", drc_mode_map[i].mode);
   }

   fprintf(stdout, "\n");
}