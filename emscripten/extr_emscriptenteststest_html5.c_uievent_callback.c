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
struct TYPE_3__ {int /*<<< orphan*/  scrollLeft; int /*<<< orphan*/  scrollTop; int /*<<< orphan*/  windowInnerHeight; int /*<<< orphan*/  windowInnerWidth; int /*<<< orphan*/  documentBodyClientHeight; int /*<<< orphan*/  documentBodyClientWidth; int /*<<< orphan*/  detail; } ;
typedef  TYPE_1__ EmscriptenUiEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

EM_BOOL uievent_callback(int eventType, const EmscriptenUiEvent *e, void *userData)
{
  printf("%s, detail: %ld, document.body.client size: (%d,%d), window.inner size: (%d,%d), scrollPos: (%d, %d)\n",
    emscripten_event_type_to_string(eventType), e->detail, e->documentBodyClientWidth, e->documentBodyClientHeight,
    e->windowInnerWidth, e->windowInnerHeight, e->scrollTop, e->scrollLeft);

  return 0;
}