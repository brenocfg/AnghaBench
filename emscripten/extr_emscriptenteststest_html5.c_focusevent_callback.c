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
struct TYPE_3__ {char* nodeName; char* id; } ;
typedef  TYPE_1__ EmscriptenFocusEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

EM_BOOL focusevent_callback(int eventType, const EmscriptenFocusEvent *e, void *userData)
{
  printf("%s, nodeName: \"%s\", id: \"%s\"\n", emscripten_event_type_to_string(eventType), e->nodeName, e->id[0] == '\0' ? "(empty string)" : e->id);

  return 0;
}