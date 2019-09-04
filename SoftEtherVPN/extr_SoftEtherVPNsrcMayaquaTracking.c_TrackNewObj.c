#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  void* UINT ;
struct TYPE_4__ {char* Name; scalar_t__ LineNumber; scalar_t__* FileName; int /*<<< orphan*/  CallStack; int /*<<< orphan*/  CreatedDate; void* Size; scalar_t__ Address; void* Id; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  GetCallStack () ; 
 int /*<<< orphan*/  InsertTrackingList (TYPE_1__*) ; 
 scalar_t__ IsMemCheck () ; 
 scalar_t__ IsTrackingEnabled () ; 
 int /*<<< orphan*/  LocalTime64 () ; 
 int /*<<< orphan*/  LockTrackingList () ; 
 int /*<<< orphan*/  OSLock (int /*<<< orphan*/ ) ; 
 TYPE_1__* OSMemoryAlloc (int) ; 
 int /*<<< orphan*/  OSUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockTrackingList () ; 
 int /*<<< orphan*/  WalkDownCallStack (int /*<<< orphan*/ ,int) ; 
 void* obj_id ; 
 int /*<<< orphan*/  obj_id_lock ; 

void TrackNewObj(UINT64 addr, char *name, UINT size)
{
	TRACKING_OBJECT *o;
	UINT new_id;
	// Validate arguments
	if (addr == 0 || name == NULL)
	{
		return;
	}

	if ((IsTrackingEnabled() && IsMemCheck()) == false)
	{
		// Don't track in detail if the memory check option is not specified
		return;
	}

	// Generate a new ID
	OSLock(obj_id_lock);
	{
		new_id = ++obj_id;
	}
	OSUnlock(obj_id_lock);

	o = OSMemoryAlloc(sizeof(TRACKING_OBJECT));
	o->Id = new_id;
	o->Address = addr;
	o->Name = name;
	o->Size = size;
	o->CreatedDate = LocalTime64();
	o->CallStack = WalkDownCallStack(GetCallStack(), 2);

	o->FileName[0] = 0;
	o->LineNumber = 0;

	LockTrackingList();
	{
		InsertTrackingList(o);
	}
	UnlockTrackingList();
}