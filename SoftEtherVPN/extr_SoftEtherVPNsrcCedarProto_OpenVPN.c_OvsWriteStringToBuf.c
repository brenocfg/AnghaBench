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
typedef  char USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 char Endian16 (char) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int MIN (int,int) ; 
 char* Malloc (int) ; 
 scalar_t__ StrLen (char*) ; 
 int StrSize (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,char*,int) ; 

void OvsWriteStringToBuf(BUF *b, char *str, UINT max_size)
{
	USHORT us;
	UINT i;
	char *tmp;
	// Validate arguments
	if (b == NULL)
	{
		return;
	}
	if (str == NULL)
	{
		str = "";
	}

	if (StrLen(str) == 0)
	{
		us = 0;
		WriteBuf(b, &us, sizeof(USHORT));
		return;
	}

	i = StrSize(str);
	i = MIN(i, max_size);
	us = Endian16((USHORT)i);
	WriteBuf(b, &us, sizeof(USHORT));

	tmp = Malloc(i);
	Copy(tmp, str, i);
	tmp[i - 1] = 0;
	WriteBuf(b, tmp, i);

	Free(tmp);
}