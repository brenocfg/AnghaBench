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
struct TYPE_4__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  MS_REG_TCP_SETTING_KEY ; 
 TYPE_1__* MsRegReadBinEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  REG_LOCAL_MACHINE ; 
 scalar_t__ SHA1_SIZE ; 

bool CiReadLastMachineHash(void *data)
{
	BUF *b = NULL;
	// Validate arguments
	if (data == NULL)
	{
		return false;
	}

#ifdef OS_WIN32
	b = MsRegReadBinEx(REG_LOCAL_MACHINE, MS_REG_TCP_SETTING_KEY, "LastMachineHash", true);
	if (b == NULL)
	{
		return false;
	}
	if (b->Size == SHA1_SIZE)
	{
		Copy(data, b->Buf, b->Size);
		FreeBuf(b);

		return true;
	}

	FreeBuf(b);
	return false;
#else	// OS_WIN32
	return false;
#endif	// OS_WIN32
}