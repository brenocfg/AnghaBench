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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* StrToBin (char*) ; 

bool StrToMac(UCHAR *mac_address, char *str)
{
	BUF *b;
	// Validate arguments
	if (mac_address == NULL || str == NULL)
	{
		return false;
	}

	b = StrToBin(str);
	if (b == NULL)
	{
		return false;
	}

	if (b->Size != 6)
	{
		FreeBuf(b);
		return false;
	}

	Copy(mac_address, b->Buf, 6);

	FreeBuf(b);

	return true;
}