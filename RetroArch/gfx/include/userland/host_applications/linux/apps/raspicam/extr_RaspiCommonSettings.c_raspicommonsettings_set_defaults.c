#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ gps; scalar_t__ sensor_mode; scalar_t__ cameraNum; scalar_t__ verbose; int /*<<< orphan*/ * filename; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  camera_name; } ;
typedef  TYPE_1__ RASPICOMMONSETTINGS_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_INFO_MAX_STR_LEN ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void raspicommonsettings_set_defaults(RASPICOMMONSETTINGS_PARAMETERS *state)
{
   strncpy(state->camera_name, "(Unknown)", MMAL_PARAMETER_CAMERA_INFO_MAX_STR_LEN);
   // We dont set width and height since these will be specific to the app being built.
   state->width = 0;
   state->height = 0;
   state->filename = NULL;
   state->verbose = 0;
   state->cameraNum = 0;
   state->sensor_mode = 0;
   state->gps = 0;
}