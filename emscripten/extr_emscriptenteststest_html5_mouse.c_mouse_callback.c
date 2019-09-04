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
struct TYPE_3__ {int screenX; scalar_t__ screenY; scalar_t__ clientX; scalar_t__ clientY; scalar_t__ buttons; scalar_t__ movementX; scalar_t__ movementY; scalar_t__ targetX; scalar_t__ targetY; int /*<<< orphan*/  button; scalar_t__ metaKey; scalar_t__ altKey; scalar_t__ shiftKey; scalar_t__ ctrlKey; } ;
typedef  TYPE_1__ EmscriptenMouseEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int EMSCRIPTEN_EVENT_CLICK ; 
 int EMSCRIPTEN_EVENT_DBLCLICK ; 
 int EMSCRIPTEN_EVENT_MOUSEDOWN ; 
 int EMSCRIPTEN_EVENT_MOUSEMOVE ; 
 int EMSCRIPTEN_EVENT_MOUSEUP ; 
 char* emscripten_event_type_to_string (int) ; 
 int gotClick ; 
 int gotDblClick ; 
 int gotMouseDown ; 
 int gotMouseMove ; 
 int gotMouseUp ; 
 int /*<<< orphan*/  instruction () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  report_result (int) ; 

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
  printf("%s, screen: (%ld,%ld), client: (%ld,%ld),%s%s%s%s button: %hu, buttons: %hu, movement: (%ld,%ld), target: (%ld, %ld)\n",
    emscripten_event_type_to_string(eventType), e->screenX, e->screenY, e->clientX, e->clientY,
    e->ctrlKey ? " CTRL" : "", e->shiftKey ? " SHIFT" : "", e->altKey ? " ALT" : "", e->metaKey ? " META" : "", 
    e->button, e->buttons, e->movementX, e->movementY, e->targetX, e->targetY);

  if (e->screenX != 0 && e->screenY != 0 && e->clientX != 0 && e->clientY != 0 && e->targetX != 0 && e->targetY != 0)
  {
    if (eventType == EMSCRIPTEN_EVENT_CLICK) gotClick = 1;
    if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN && e->buttons != 0) gotMouseDown = 1;
    if (eventType == EMSCRIPTEN_EVENT_DBLCLICK) gotDblClick = 1;
    if (eventType == EMSCRIPTEN_EVENT_MOUSEUP) gotMouseUp = 1;
    if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE && (e->movementX != 0 || e->movementY != 0)) gotMouseMove = 1;
  }

  if (eventType == EMSCRIPTEN_EVENT_CLICK && e->screenX == -500000)
  {
    printf("ERROR! Received an event to a callback that should have been unregistered!\n");
    gotClick = 0;
    report_result(1);
  }

  instruction();
  return 0;
}