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
typedef  int /*<<< orphan*/  bs ;
struct TYPE_4__ {int Halt; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  DirName; int /*<<< orphan*/  MinFreeSpace; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ ERASER ;

/* Variables and functions */
 int /*<<< orphan*/  ELog (TYPE_1__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EraserMain (TYPE_1__*) ; 
 int /*<<< orphan*/  GetEraserCheckInterval () ; 
 int /*<<< orphan*/  ToStrByte (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void EraserThread(THREAD *t, void *p)
{
	ERASER *e = (ERASER *)p;
	char bs[64];
	// Validate arguments
	if (t == NULL || e == NULL)
	{
		return;
	}

	// Start monitoring
	ToStrByte(bs, sizeof(bs), e->MinFreeSpace);
	ELog(e, "LE_START", e->DirName, bs);

	while (e->Halt == false)
	{
		// Check the amount of free space on the disk periodically
		EraserMain(e);

		Wait(e->HaltEvent, GetEraserCheckInterval());
	}
}