#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  canvasY; int /*<<< orphan*/  canvasX; int /*<<< orphan*/  buttons; int /*<<< orphan*/  button; scalar_t__ metaKey; scalar_t__ altKey; scalar_t__ shiftKey; scalar_t__ ctrlKey; int /*<<< orphan*/  clientY; int /*<<< orphan*/  clientX; int /*<<< orphan*/  screenY; int /*<<< orphan*/  screenX; } ;
struct TYPE_5__ {int /*<<< orphan*/  deltaMode; scalar_t__ deltaZ; scalar_t__ deltaY; scalar_t__ deltaX; TYPE_1__ mouse; } ;
typedef  TYPE_2__ EmscriptenWheelEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,float,int /*<<< orphan*/ ) ; 

EM_BOOL wheel_callback(int eventType, const EmscriptenWheelEvent *e, void *userData)
{
  printf("%s, screen: (%ld,%ld), client: (%ld,%ld),%s%s%s%s button: %hu, buttons: %hu, canvas: (%ld,%ld), delta:(%g,%g,%g), deltaMode:%lu\n",
    emscripten_event_type_to_string(eventType), e->mouse.screenX, e->mouse.screenY, e->mouse.clientX, e->mouse.clientY,
    e->mouse.ctrlKey ? " CTRL" : "", e->mouse.shiftKey ? " SHIFT" : "", e->mouse.altKey ? " ALT" : "", e->mouse.metaKey ? " META" : "", 
    e->mouse.button, e->mouse.buttons, e->mouse.canvasX, e->mouse.canvasY,
    (float)e->deltaX, (float)e->deltaY, (float)e->deltaZ, e->deltaMode);

  return 0;
}