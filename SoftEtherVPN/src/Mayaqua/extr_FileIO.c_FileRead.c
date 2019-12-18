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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int HamMode; int /*<<< orphan*/  HamBuf; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ IO ;

/* Variables and functions */
 int /*<<< orphan*/  KS_ADD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_IO_READ_COUNT ; 
 int /*<<< orphan*/  KS_IO_TOTAL_READ_SIZE ; 
 int OSFileRead (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ ReadBuf (int /*<<< orphan*/ ,void*,scalar_t__) ; 

bool FileRead(IO *o, void *buf, UINT size)
{
	// Validate arguments
	if (o == NULL || buf == NULL)
	{
		return false;
	}

	// KS
	KS_INC(KS_IO_READ_COUNT);
	KS_ADD(KS_IO_TOTAL_READ_SIZE, size);

	if (size == 0)
	{
		return true;
	}

	if (o->HamMode == false)
	{
		return OSFileRead(o->pData, buf, size);
	}
	else
	{
		return ReadBuf(o->HamBuf, buf, size) == size ? true : false;
	}
}