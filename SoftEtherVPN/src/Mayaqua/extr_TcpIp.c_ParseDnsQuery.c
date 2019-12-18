#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  tmp ;
typedef  char USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int Endian16 (char) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetNextByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int ReadBuf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

bool ParseDnsQuery(char *name, UINT name_size, void *data, UINT data_size)
{
	BUF *b;
	char tmp[257];
	bool ok = true;
	USHORT val;
	// Validate arguments
	if (name == NULL || data == NULL || data_size == 0)
	{
		return false;
	}
	StrCpy(name, name_size, "");

	b = NewBuf();
	WriteBuf(b, data, data_size);
	SeekBuf(b, 0, 0);

	while (true)
	{
		UINT next_len = (UINT)GetNextByte(b);
		if (next_len > 0)
		{
			// Read only the specified length
			Zero(tmp, sizeof(tmp));
			if (ReadBuf(b, tmp, next_len) != next_len)
			{
				ok = false;
				break;
			}
			// Append
			if (StrLen(name) != 0)
			{
				StrCat(name, name_size, ".");
			}
			StrCat(name, name_size, tmp);
		}
		else
		{
			// Read all
			break;
		}
	}

	if (ReadBuf(b, &val, sizeof(val)) != sizeof(val))
	{
		ok = false;
	}
	else
	{
		if (Endian16(val) != 0x01 && Endian16(val) != 0x0c)
		{
			ok = false;
		}
	}

	if (ReadBuf(b, &val, sizeof(val)) != sizeof(val))
	{
		ok = false;
	}
	else
	{
		if (Endian16(val) != 0x01)
		{
			ok = false;
		}
	}

	FreeBuf(b);

	if (ok == false || StrLen(name) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}