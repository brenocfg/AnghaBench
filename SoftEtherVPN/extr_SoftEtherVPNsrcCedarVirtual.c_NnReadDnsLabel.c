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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int ReadBuf (int /*<<< orphan*/ *,int*,int) ; 

bool NnReadDnsLabel(BUF *buf)
{
	UCHAR c;
	UCHAR tmp[256];
	// Validate arguments
	if (buf == NULL)
	{
		return false;
	}

LABEL_START:

	if (ReadBuf(buf, &c, 1) != 1)
	{
		return false;
	}

	if (c == 0)
	{
		return true;
	}

	if (c & 0xC0)
	{
		// Compression label
		if (ReadBuf(buf, &c, 1) != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		// Usual label
		if (ReadBuf(buf, tmp, c) != c)
		{
			return false;
		}
		else
		{
			goto LABEL_START;
		}
	}

}