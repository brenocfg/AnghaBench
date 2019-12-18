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
typedef  scalar_t__ OMX_EVENTTYPE ;

/* Variables and functions */
 size_t MMALOMX_SAT (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vcos_countof (char const**) ; 

const char *mmalomx_event_to_string(OMX_EVENTTYPE event)
{
  static const char *names[] = {
    "OMX_EventCmdComplete", "OMX_EventError", "OMX_EventMark",
    "OMX_EventPortSettingsChanged", "OMX_EventBufferFlag",
    "OMX_EventResourcesAcquired", "OMX_EventComponentResumed",
    "OMX_EventDynamicResourcesAvailable", "OMX_EventPortFormatDetected",
    "OMX_Event unknown"
  };

  return names[MMALOMX_SAT((int)event, 0, (int)vcos_countof(names)-1)];
}