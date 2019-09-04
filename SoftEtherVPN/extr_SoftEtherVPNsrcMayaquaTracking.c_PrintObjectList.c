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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int /*<<< orphan*/  LineNumber; int /*<<< orphan*/  FileName; int /*<<< orphan*/  Size; int /*<<< orphan*/  Address; int /*<<< orphan*/  Name; int /*<<< orphan*/  Id; int /*<<< orphan*/  CreatedDate; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetTimeStrMilli (char*,int,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  Print (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TrackGetObjSymbolInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  UINT64ToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_TO_POINTER (int /*<<< orphan*/ ) ; 

void PrintObjectList(TRACKING_OBJECT *o)
{
	char tmp[MAX_SIZE];
	SYSTEMTIME t;
	UINT64ToSystem(&t, o->CreatedDate);
	GetTimeStrMilli(tmp, sizeof(tmp), &t);
	TrackGetObjSymbolInfo(o);
	Print("%-4u - [%-6s] %s 0x%p size=%-5u %11s %u\n",
		o->Id, o->Name, tmp, UINT64_TO_POINTER(o->Address), o->Size, o->FileName, o->LineNumber);
}