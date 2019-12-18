#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {int Current; int Size; scalar_t__ Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ReadBuf (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_1__*,int,int) ; 
 int StrLen (char*) ; 
 char* ZeroMalloc (size_t) ; 

char *CfgReadNextLine(BUF *b)
{
	char *tmp;
	char *buf;
	UINT len;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	// Examine the number of characters up to the next newline
	tmp = (char *)b->Buf + b->Current;
	if ((b->Size - b->Current) == 0)
	{
		// Read to the end
		return NULL;
	}
	len = 0;
	while (true)
	{
		if (tmp[len] == 13 || tmp[len] == 10)
		{
			if (tmp[len] == 13)
			{
				if (len < (b->Size - b->Current))
				{
					len++;
				}
			}
			break;
		}
		len++;
		if (len >= (b->Size - b->Current))
		{
			break;
		}
	}

	// Read ahead only 'len' bytes
	buf = ZeroMalloc(len + 1);
	ReadBuf(b, buf, len);
	SeekBuf(b, 1, 1);

	if (StrLen(buf) >= 1)
	{
		if (buf[StrLen(buf) - 1] == 13)
		{
			buf[StrLen(buf) - 1] = 0;
		}
	}

	return buf;
}