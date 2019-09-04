#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int EMSCRIPTEN_EVENT_POINTERLOCKERROR ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_result (int) ; 

EM_BOOL pointerlockerror_callback(int eventType, const void *reserved, void *userData) {
  if (eventType != EMSCRIPTEN_EVENT_POINTERLOCKERROR) {
    printf("ERROR! invalid event type for 'pointerlockerror' callback\n");
    report_result(1);
    return 0;
  }

  printf("SUCCESS! received 'pointerlockerror' event\n");
  report_result(0);

  return 0;
}