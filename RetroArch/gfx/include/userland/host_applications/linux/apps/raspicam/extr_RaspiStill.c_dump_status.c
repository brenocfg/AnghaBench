#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nextFrameMethod; char* description; } ;
struct TYPE_5__ {int width; int height; int quality; scalar_t__ enable; } ;
struct TYPE_6__ {int quality; int timeout; int timelapse; char* linkname; scalar_t__ frameNextMethod; int numExifTags; char** exifTags; int /*<<< orphan*/  camera_parameters; int /*<<< orphan*/  preview_parameters; scalar_t__ enableExifTags; scalar_t__ fullResPreview; TYPE_1__ thumbnailConfig; scalar_t__ wantRAW; int /*<<< orphan*/  common_settings; } ;
typedef  TYPE_2__ RASPISTILL_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* next_frame_description ; 
 int next_frame_description_size ; 
 int /*<<< orphan*/  raspicamcontrol_dump_parameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspicommonsettings_dump_parameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspipreview_dump_parameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_status(RASPISTILL_STATE *state)
{
   int i;

   if (!state)
   {
      vcos_assert(0);
      return;
   }

   raspicommonsettings_dump_parameters(&state->common_settings);

   fprintf(stderr, "Quality %d, Raw %s\n", state->quality, state->wantRAW ? "yes" : "no");
   fprintf(stderr, "Thumbnail enabled %s, width %d, height %d, quality %d\n",
           state->thumbnailConfig.enable ? "Yes":"No", state->thumbnailConfig.width,
           state->thumbnailConfig.height, state->thumbnailConfig.quality);

   fprintf(stderr, "Time delay %d, Timelapse %d\n", state->timeout, state->timelapse);
   fprintf(stderr, "Link to latest frame enabled ");
   if (state->linkname)
   {
      fprintf(stderr, " yes, -> %s\n", state->linkname);
   }
   else
   {
      fprintf(stderr, " no\n");
   }
   fprintf(stderr, "Full resolution preview %s\n", state->fullResPreview ? "Yes": "No");

   fprintf(stderr, "Capture method : ");
   for (i=0; i<next_frame_description_size; i++)
   {
      if (state->frameNextMethod == next_frame_description[i].nextFrameMethod)
         fprintf(stderr, "%s", next_frame_description[i].description);
   }
   fprintf(stderr, "\n\n");

   if (state->enableExifTags)
   {
      if (state->numExifTags)
      {
         fprintf(stderr, "User supplied EXIF tags :\n");

         for (i=0; i<state->numExifTags; i++)
         {
            fprintf(stderr, "%s", state->exifTags[i]);
            if (i != state->numExifTags-1)
               fprintf(stderr, ",");
         }
         fprintf(stderr, "\n\n");
      }
   }
   else
      fprintf(stderr, "EXIF tags disabled\n");

   raspipreview_dump_parameters(&state->preview_parameters);
   raspicamcontrol_dump_parameters(&state->camera_parameters);
}