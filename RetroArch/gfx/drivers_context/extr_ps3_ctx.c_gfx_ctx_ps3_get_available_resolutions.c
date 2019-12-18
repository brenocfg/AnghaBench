#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  videomode ;
typedef  int uint32_t ;
typedef  unsigned int uint16_t ;
struct TYPE_9__ {int id; int idx; } ;
struct TYPE_8__ {int id; } ;
struct TYPE_10__ {int check; int count; int* list; TYPE_2__ current; TYPE_1__ initial; } ;
struct TYPE_11__ {TYPE_3__ resolutions; } ;
struct TYPE_12__ {TYPE_4__ screen; } ;
struct TYPE_13__ {TYPE_5__ console; } ;
typedef  TYPE_6__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_VIDEO_OUT_ASPECT_AUTO ; 
 int /*<<< orphan*/  CELL_VIDEO_OUT_PRIMARY ; 
 int CELL_VIDEO_OUT_RESOLUTION_1080 ; 
 int CELL_VIDEO_OUT_RESOLUTION_1280x1080 ; 
 int CELL_VIDEO_OUT_RESOLUTION_1440x1080 ; 
 int CELL_VIDEO_OUT_RESOLUTION_1600x1080 ; 
 int CELL_VIDEO_OUT_RESOLUTION_480 ; 
 int CELL_VIDEO_OUT_RESOLUTION_576 ; 
 int CELL_VIDEO_OUT_RESOLUTION_720 ; 
 int CELL_VIDEO_OUT_RESOLUTION_960x1080 ; 
 scalar_t__ cellVideoOutGetResolutionAvailability (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* global_get_ptr () ; 
 int* malloc (int) ; 

__attribute__((used)) static void gfx_ctx_ps3_get_available_resolutions(void)
{
   unsigned i;
   uint32_t videomode[] = {
      CELL_VIDEO_OUT_RESOLUTION_480,
      CELL_VIDEO_OUT_RESOLUTION_576,
      CELL_VIDEO_OUT_RESOLUTION_960x1080,
      CELL_VIDEO_OUT_RESOLUTION_720,
      CELL_VIDEO_OUT_RESOLUTION_1280x1080,
      CELL_VIDEO_OUT_RESOLUTION_1440x1080,
      CELL_VIDEO_OUT_RESOLUTION_1600x1080,
      CELL_VIDEO_OUT_RESOLUTION_1080
   };
   uint32_t resolution_count = 0;
   bool defaultresolution    = true;
   uint16_t num_videomodes   = sizeof(videomode) / sizeof(uint32_t);
   global_t       *global    = global_get_ptr();

   if (global->console.screen.resolutions.check)
      return;

   for (i = 0; i < num_videomodes; i++)
   {
      if (cellVideoOutGetResolutionAvailability(
               CELL_VIDEO_OUT_PRIMARY, videomode[i],
               CELL_VIDEO_OUT_ASPECT_AUTO, 0))
         resolution_count++;
   }

   global->console.screen.resolutions.count = 0;
   global->console.screen.resolutions.list  =
      malloc(resolution_count * sizeof(uint32_t));

   for (i = 0; i < num_videomodes; i++)
   {
      if (cellVideoOutGetResolutionAvailability(
               CELL_VIDEO_OUT_PRIMARY,
               videomode[i],
               CELL_VIDEO_OUT_ASPECT_AUTO, 0))
      {
         global->console.screen.resolutions.list[
            global->console.screen.resolutions.count++] = videomode[i];
         global->console.screen.resolutions.initial.id = videomode[i];

         if (global->console.screen.resolutions.current.id == videomode[i])
         {
            defaultresolution = false;
            global->console.screen.resolutions.current.idx =
               global->console.screen.resolutions.count-1;
         }
      }
   }

   /* In case we didn't specify a resolution -
    * make the last resolution
      that was added to the list (the highest resolution)
      the default resolution */
   if (global->console.screen.resolutions.current.id > num_videomodes || defaultresolution)
    {
      global->console.screen.resolutions.current.idx = resolution_count - 1;
      global->console.screen.resolutions.current.id = global->console.screen.resolutions.list[global->console.screen.resolutions.current.idx];
    }

   global->console.screen.resolutions.check = true;
}