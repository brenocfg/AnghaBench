#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ line; int /*<<< orphan*/  filename; } ;
struct TYPE_4__ {scalar_t__ LineNumber; scalar_t__* FileName; TYPE_3__* CallStack; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  GetCallStackSymbolInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 

void TrackGetObjSymbolInfo(TRACKING_OBJECT *o)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	if (!(o->LineNumber == 0 && o->FileName[0] == 0))
	{
		return;
	}

	if (o->CallStack != NULL)
	{
		GetCallStackSymbolInfo(o->CallStack);
		if (StrLen(o->CallStack->filename) != 0 && o->CallStack->line != 0)
		{
			StrCpy(o->FileName, sizeof(o->FileName), o->CallStack->filename);
			o->LineNumber = o->CallStack->line;
		}
	}
}