#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ Size; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MD5_SIZE ; 
 int /*<<< orphan*/  Md5 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* MemToBuf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 TYPE_1__* StrToBin (char*) ; 

BUF *IkeStrToVendorId(char *str)
{
	// Validate arguments
	if (IsEmptyStr(str))
	{
		return NULL;
	}

	if (StartWith(str, "0x"))
	{
		BUF *buf = StrToBin(str + 2);

		if (buf == NULL || buf->Size == 0)
		{
			FreeBuf(buf);
			return NULL;
		}

		return buf;
	}
	else
	{
		BUF *buf;
		UCHAR hash[MD5_SIZE];

		Md5(hash, str, StrLen(str));

		buf = MemToBuf(hash, sizeof(hash));

		return buf;
	}
}