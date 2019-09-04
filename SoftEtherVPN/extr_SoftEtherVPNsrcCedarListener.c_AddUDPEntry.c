#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  SessionKey32; TYPE_2__* Session; } ;
typedef  TYPE_1__ UDP_ENTRY ;
struct TYPE_10__ {int /*<<< orphan*/  UDPEntryList; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  SessionKey32; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void AddUDPEntry(CEDAR *cedar, SESSION *session)
{
	UDP_ENTRY *e;
	// Validate arguments
	if (cedar == NULL || session == NULL)
	{
		return;
	}

	e = ZeroMalloc(sizeof(UDP_ENTRY));
	e->Session = session;
	e->SessionKey32 = session->SessionKey32;
	AddRef(session->ref);

	LockList(cedar->UDPEntryList);
	{
		Add(cedar->UDPEntryList, e);
	}
	UnlockList(cedar->UDPEntryList);

	Debug("UDP_Entry Added.\n");
}