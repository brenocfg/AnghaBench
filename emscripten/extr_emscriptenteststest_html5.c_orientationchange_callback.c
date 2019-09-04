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
struct TYPE_3__ {int orientationAngle; int orientationIndex; } ;
typedef  TYPE_1__ EmscriptenOrientationChangeEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

EM_BOOL orientationchange_callback(int eventType, const EmscriptenOrientationChangeEvent *e, void *userData)
{
  printf("%s, orientationAngle: %d, orientationIndex: %d\n", emscripten_event_type_to_string(eventType), e->orientationAngle, e->orientationIndex);

  return 0;
}