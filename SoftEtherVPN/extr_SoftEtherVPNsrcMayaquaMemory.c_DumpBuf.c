#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreate (char*) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool DumpBuf(BUF *b, char *filename)
{
	IO *o;
	// Validate arguments
	if (b == NULL || filename == NULL)
	{
		return false;
	}

	o = FileCreate(filename);
	if (o == NULL)
	{
		return false;
	}
	FileWrite(o, b->Buf, b->Size);
	FileClose(o);

	return true;
}