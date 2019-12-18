#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  size_str ;
struct TYPE_8__ {scalar_t__ Size; int /*<<< orphan*/  EntryName; int /*<<< orphan*/ * Data; } ;
typedef  TYPE_1__ WPC_ENTRY ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {scalar_t__ Size; scalar_t__ Current; scalar_t__ Buf; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int ReadBuf (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ ToInt (char*) ; 
 int WPC_DATA_ENTRY_SIZE ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

LIST *WpcParseDataEntry(BUF *b)
{
	char entry_name[WPC_DATA_ENTRY_SIZE];
	char size_str[11];
	LIST *o;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	SeekBuf(b, 0, 0);

	o = NewListFast(NULL);

	while (true)
	{
		UINT size;
		WPC_ENTRY *e;

		if (ReadBuf(b, entry_name, WPC_DATA_ENTRY_SIZE) != WPC_DATA_ENTRY_SIZE)
		{
			break;
		}

		Zero(size_str, sizeof(size_str));
		if (ReadBuf(b, size_str, 10) != 10)
		{
			break;
		}

		size = ToInt(size_str);
		if ((b->Size - b->Current) < size)
		{
			break;
		}

		e = ZeroMalloc(sizeof(WPC_ENTRY));
		e->Data = (UCHAR *)b->Buf + b->Current;
		Copy(e->EntryName, entry_name, WPC_DATA_ENTRY_SIZE);
		e->Size = size;

		SeekBuf(b, size, 1);

		Add(o, e);
	}

	return o;
}