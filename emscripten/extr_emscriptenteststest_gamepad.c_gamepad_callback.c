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
struct TYPE_3__ {double timestamp; int connected; int numAxes; int numButtons; double* axis; int* digitalButton; double* analogButton; int /*<<< orphan*/  mapping; int /*<<< orphan*/  id; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ EmscriptenGamepadEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

EM_BOOL gamepad_callback(int eventType, const EmscriptenGamepadEvent *e, void *userData)
{
  printf("%s: timeStamp: %g, connected: %d, index: %ld, numAxes: %d, numButtons: %d, id: \"%s\", mapping: \"%s\"\n",
    eventType != 0 ? emscripten_event_type_to_string(eventType) : "Gamepad state", e->timestamp, e->connected, e->index, 
    e->numAxes, e->numButtons, e->id, e->mapping);

  if (e->connected)
  {
    for(int i = 0; i < e->numAxes; ++i)
      printf("Axis %d: %g\n", i, e->axis[i]);

    for(int i = 0; i < e->numButtons; ++i)
      printf("Button %d: Digital: %d, Analog: %g\n", i, e->digitalButton[i], e->analogButton[i]);
  }

  return 0;
}