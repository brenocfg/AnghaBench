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
struct TYPE_3__ {int isFullscreen; int fullscreenEnabled; char* nodeName; char* id; int elementWidth; int elementHeight; int screenWidth; int screenHeight; } ;
typedef  TYPE_1__ EmscriptenFullscreenChangeEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int callCount ; 
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  report_result (int) ; 

EM_BOOL fullscreenchange_callback(int eventType, const EmscriptenFullscreenChangeEvent *e, void *userData)
{
  printf("%s, isFullscreen: %d, fullscreenEnabled: %d, fs element nodeName: \"%s\", fs element id: \"%s\". New size: %dx%d pixels. Screen size: %dx%d pixels.\n",
    emscripten_event_type_to_string(eventType), e->isFullscreen, e->fullscreenEnabled, e->nodeName, e->id, e->elementWidth, e->elementHeight, e->screenWidth, e->screenHeight);

  ++callCount;
  if (callCount == 1) { // Transitioned to fullscreen.
    if (!e->isFullscreen) {
      report_result(1);
    }
  } else if (callCount == 2) { // Transitioned to windowed, we must be back to the default pixel size 300x150.
    if (e->isFullscreen || e->elementWidth != 300 || e->elementHeight != 150) {
      report_result(1);
    } else {
      report_result(0);
    }
  }
  return 0;
}