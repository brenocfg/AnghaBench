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
struct TYPE_3__ {int isActive; char* nodeName; char* id; } ;
typedef  TYPE_1__ EmscriptenPointerlockChangeEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*,char*) ; 

EM_BOOL pointerlockchange_callback(int eventType, const EmscriptenPointerlockChangeEvent *e, void *userData)
{
  printf("%s, isActive: %d, pointerlock element nodeName: \"%s\", id: \"%s\"\n",
    emscripten_event_type_to_string(eventType), e->isActive, e->nodeName, e->id);

  return 0;
}