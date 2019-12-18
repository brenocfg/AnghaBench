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
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int timeout; int bitrate; int intraperiod; int demoInterval; int immutableInput; int onTime; int offTime; int segmentNumber; int intra_refresh_type; int netListen; int slices; int /*<<< orphan*/  camera_parameters; int /*<<< orphan*/  preview_parameters; int /*<<< orphan*/  addSPSTiming; scalar_t__ save_pts; scalar_t__ frame; scalar_t__ inlineMotionVectors; scalar_t__ splitWait; scalar_t__ splitNow; scalar_t__ segmentWrap; scalar_t__ segmentSize; scalar_t__ bInlineHeaders; scalar_t__ bCapturing; int /*<<< orphan*/  waitMethod; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; scalar_t__ demoMode; scalar_t__ quantisationParameter; int /*<<< orphan*/  framerate; int /*<<< orphan*/  encoding; TYPE_2__ common_settings; } ;
typedef  TYPE_1__ RASPIVID_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENCODING_H264 ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_4 ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_HIGH ; 
 int /*<<< orphan*/  VIDEO_FRAME_RATE_NUM ; 
 int /*<<< orphan*/  WAIT_METHOD_NONE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raspicommonsettings_set_defaults (TYPE_2__*) ; 
 int /*<<< orphan*/  raspipreview_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void default_status(RASPIVID_STATE *state)
{
   if (!state)
   {
      vcos_assert(0);
      return;
   }

   // Default everything to zero
   memset(state, 0, sizeof(RASPIVID_STATE));

   raspicommonsettings_set_defaults(&state->common_settings);

   // Now set anything non-zero
   state->timeout = -1; // replaced with 5000ms later if unset
   state->common_settings.width = 1920;       // Default to 1080p
   state->common_settings.height = 1080;
   state->encoding = MMAL_ENCODING_H264;
   state->bitrate = 17000000; // This is a decent default bitrate for 1080p
   state->framerate = VIDEO_FRAME_RATE_NUM;
   state->intraperiod = -1;    // Not set
   state->quantisationParameter = 0;
   state->demoMode = 0;
   state->demoInterval = 250; // ms
   state->immutableInput = 1;
   state->profile = MMAL_VIDEO_PROFILE_H264_HIGH;
   state->level = MMAL_VIDEO_LEVEL_H264_4;
   state->waitMethod = WAIT_METHOD_NONE;
   state->onTime = 5000;
   state->offTime = 5000;
   state->bCapturing = 0;
   state->bInlineHeaders = 0;
   state->segmentSize = 0;  // 0 = not segmenting the file.
   state->segmentNumber = 1;
   state->segmentWrap = 0; // Point at which to wrap segment number back to 1. 0 = no wrap
   state->splitNow = 0;
   state->splitWait = 0;
   state->inlineMotionVectors = 0;
   state->intra_refresh_type = -1;
   state->frame = 0;
   state->save_pts = 0;
   state->netListen = false;
   state->addSPSTiming = MMAL_FALSE;
   state->slices = 1;

   // Setup preview window defaults
   raspipreview_set_defaults(&state->preview_parameters);

   // Set up the camera_parameters to default
   raspicamcontrol_set_defaults(&state->camera_parameters);
}