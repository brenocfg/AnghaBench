#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  event_handle; } ;
typedef  int /*<<< orphan*/  SL_UNICODE ;
typedef  TYPE_1__ SL_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * IoCreateNotificationEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  SlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  SlFreeUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SlGetUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SlNewUnicode (char*) ; 
 TYPE_1__* SlZeroMalloc (int) ; 

SL_EVENT *SlNewEvent(char *name)
{
	SL_UNICODE *unicode_name;
	SL_EVENT *event;
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	// Convert to Unicode name
	unicode_name = SlNewUnicode(name);
	if (unicode_name == NULL)
	{
		return NULL;
	}

	// Memory allocation
	event = SlZeroMalloc(sizeof(SL_EVENT));
	if (event == NULL)
	{
		SlFreeUnicode(unicode_name);
		return NULL;
	}

	// Create an event
	event->event = IoCreateNotificationEvent(SlGetUnicode(unicode_name), &event->event_handle);
	if (event->event == NULL)
	{
		SlFree(event);
		SlFreeUnicode(unicode_name);
		return NULL;
	}

	// Initialize the event
	KeInitializeEvent(event->event, NotificationEvent, FALSE);
	KeClearEvent(event->event);

	// Release the string
	SlFreeUnicode(unicode_name);

	return event;
}