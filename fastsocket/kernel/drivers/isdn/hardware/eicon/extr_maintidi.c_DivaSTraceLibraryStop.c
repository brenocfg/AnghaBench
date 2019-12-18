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
struct TYPE_4__ {int /*<<< orphan*/  Id; } ;
struct TYPE_5__ {int removal_state; TYPE_1__ e; } ;
typedef  TYPE_2__ diva_strace_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ScheduleNextTraceRequest (TYPE_2__*) ; 

__attribute__((used)) static int DivaSTraceLibraryStop  (void* hLib) {
  diva_strace_context_t* pLib = (diva_strace_context_t*)hLib;

  if (!pLib->e.Id) { /* Was never started/assigned */
    return (1);
  }

  switch (pLib->removal_state) {
    case 0:
      pLib->removal_state = 1;
      ScheduleNextTraceRequest(pLib);
      break;

    case 3:
      return (1);
  }

  return (0);
}