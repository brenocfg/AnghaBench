#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; TYPE_3__* es; int /*<<< orphan*/  encoding; } ;
struct TYPE_6__ {int x; int y; int width; int height; } ;
struct TYPE_7__ {int width; int height; TYPE_1__ crop; } ;
struct TYPE_8__ {TYPE_2__ video; } ;
typedef  TYPE_4__ MMAL_ES_FORMAT_T ;

/* Variables and functions */
 scalar_t__ MMAL_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void log_video_format(MMAL_ES_FORMAT_T *format)
{
   if (format->type != MMAL_ES_TYPE_VIDEO)
      return;

   fprintf(stderr, "fourcc: %4.4s, width: %i, height: %i, (%i,%i,%i,%i)\n",
            (char *)&format->encoding,
            format->es->video.width, format->es->video.height,
            format->es->video.crop.x, format->es->video.crop.y,
            format->es->video.crop.width, format->es->video.crop.height);
}