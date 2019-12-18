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
typedef  int /*<<< orphan*/  UNICODE ;
struct TYPE_5__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  event_handle; } ;
typedef  TYPE_1__ NEO_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IoCreateNotificationEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoFree (TYPE_1__*) ; 
 TYPE_1__* NeoZeroMalloc (int) ; 
 int /*<<< orphan*/ * NewUnicode (char*) ; 
 int /*<<< orphan*/  NotificationEvent ; 

NEO_EVENT *NeoNewEvent(char *name)
{
	UNICODE *unicode_name;
	NEO_EVENT *event;
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	// Convert the name to Unicode
	unicode_name = NewUnicode(name);
	if (unicode_name == NULL)
	{
		return NULL;
	}

	// Memory allocation
	event = NeoZeroMalloc(sizeof(NEO_EVENT));
	if (event == NULL)
	{
		FreeUnicode(unicode_name);
		return NULL;
	}

	// Create an Event
	event->event = IoCreateNotificationEvent(GetUnicode(unicode_name), &event->event_handle);
	if (event->event == NULL)
	{
		NeoFree(event);
		FreeUnicode(unicode_name);
		return NULL;
	}

	// Initialize the event
	KeInitializeEvent(event->event, NotificationEvent, FALSE);
	KeClearEvent(event->event);

	// Release a string
	FreeUnicode(unicode_name);

	return event;
}