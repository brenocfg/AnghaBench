#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enable; int width; int height; int quality; } ;
struct TYPE_6__ {int timeout; int quality; int demoInterval; int enableExifTags; int /*<<< orphan*/  raspitex_state; int /*<<< orphan*/  camera_parameters; int /*<<< orphan*/  preview_parameters; scalar_t__ restart_interval; scalar_t__ timestamp; scalar_t__ datetime; scalar_t__ burstCaptureMode; scalar_t__ glCapture; scalar_t__ useGL; int /*<<< orphan*/  frameNextMethod; scalar_t__ fullResPreview; scalar_t__ timelapse; scalar_t__ numExifTags; int /*<<< orphan*/  encoding; int /*<<< orphan*/ * encoder_pool; int /*<<< orphan*/ * encoder_connection; int /*<<< orphan*/ * preview_connection; int /*<<< orphan*/ * encoder_component; int /*<<< orphan*/ * camera_component; scalar_t__ demoMode; TYPE_1__ thumbnailConfig; scalar_t__ frameStart; int /*<<< orphan*/ * linkname; scalar_t__ wantRAW; int /*<<< orphan*/  common_settings; } ;
typedef  TYPE_2__ RASPISTILL_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_NEXT_SINGLE ; 
 int /*<<< orphan*/  MMAL_ENCODING_JPEG ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspicommonsettings_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspipreview_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspitex_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void default_status(RASPISTILL_STATE *state)
{
   if (!state)
   {
      vcos_assert(0);
      return;
   }

   memset(state, 0, sizeof(*state));

   raspicommonsettings_set_defaults(&state->common_settings);

   state->timeout = -1; // replaced with 5000ms later if unset
   state->quality = 85;
   state->wantRAW = 0;
   state->linkname = NULL;
   state->frameStart = 0;
   state->thumbnailConfig.enable = 1;
   state->thumbnailConfig.width = 64;
   state->thumbnailConfig.height = 48;
   state->thumbnailConfig.quality = 35;
   state->demoMode = 0;
   state->demoInterval = 250; // ms
   state->camera_component = NULL;
   state->encoder_component = NULL;
   state->preview_connection = NULL;
   state->encoder_connection = NULL;
   state->encoder_pool = NULL;
   state->encoding = MMAL_ENCODING_JPEG;
   state->numExifTags = 0;
   state->enableExifTags = 1;
   state->timelapse = 0;
   state->fullResPreview = 0;
   state->frameNextMethod = FRAME_NEXT_SINGLE;
   state->useGL = 0;
   state->glCapture = 0;
   state->burstCaptureMode=0;
   state->datetime = 0;
   state->timestamp = 0;
   state->restart_interval = 0;

   // Setup preview window defaults
   raspipreview_set_defaults(&state->preview_parameters);

   // Set up the camera_parameters to default
   raspicamcontrol_set_defaults(&state->camera_parameters);

   // Set initial GL preview state
   raspitex_set_defaults(&state->raspitex_state);
}