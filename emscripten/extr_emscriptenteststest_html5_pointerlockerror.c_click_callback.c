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
struct TYPE_3__ {scalar_t__ screenX; scalar_t__ screenY; scalar_t__ clientX; scalar_t__ clientY; scalar_t__ canvasX; scalar_t__ canvasY; scalar_t__ targetX; scalar_t__ targetY; } ;
typedef  TYPE_1__ EmscriptenMouseEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;
typedef  scalar_t__ EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int EMSCRIPTEN_EVENT_CLICK ; 
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  TEST_RESULT (scalar_t__) ; 
 scalar_t__ emscripten_request_pointerlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gotClick ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_result (int) ; 

EM_BOOL click_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
  if (e->screenX != 0 && e->screenY != 0 && e->clientX != 0 && e->clientY != 0 && e->canvasX != 0 && e->canvasY != 0 && e->targetX != 0 && e->targetY != 0)
  {
    if (eventType == EMSCRIPTEN_EVENT_CLICK && !gotClick) {
      gotClick = 1;
      printf("Request pointer lock...\n");
      EMSCRIPTEN_RESULT ret = emscripten_request_pointerlock(0, 0);
      TEST_RESULT(ret);
      if (ret != EMSCRIPTEN_RESULT_SUCCESS) {
        printf("ERROR! emscripten_request_pointerlock() failure\n");
        report_result(1);
      }
    }
  }

  return 0;
}