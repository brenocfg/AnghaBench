#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_4__ {int scaleMode; int canvasResolutionScaleMode; int filteringMode; int /*<<< orphan*/  canvasResizedCallback; } ;
typedef  TYPE_1__ EmscriptenFullscreenStrategy ;
typedef  int /*<<< orphan*/  EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_RESULT (void (*) (int,int,int)) ; 
 int /*<<< orphan*/  emscripten_request_fullscreen_strategy (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_canvassize_changed ; 

void requestFullscreen(int scaleMode, int canvasResolutionScaleMode, int filteringMode)
{
  EmscriptenFullscreenStrategy s;
  memset(&s, 0, sizeof(s));
  s.scaleMode = scaleMode;
  s.canvasResolutionScaleMode = canvasResolutionScaleMode;
  s.filteringMode = filteringMode;
  s.canvasResizedCallback = on_canvassize_changed;
  EMSCRIPTEN_RESULT ret = emscripten_request_fullscreen_strategy(0, 1, &s);
  TEST_RESULT(requestFullscreen);
}