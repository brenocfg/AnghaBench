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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  FIFO ;

/* Variables and functions */
 scalar_t__ FifoPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FifoSize (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 

UINT OvsPeekStringFromFifo(FIFO *f, char *str, UINT str_size)
{
	UINT i;
	bool ok = false;
	// Validate arguments
	if (f == NULL || str == NULL || str_size == 0)
	{
		return 0;
	}

	StrCpy(str, str_size, "");

	for (i = 0;i < MIN(str_size, FifoSize(f));i++)
	{
		char c = *(((char *)FifoPtr(f)) + i);

		if (c != 0)
		{
			str[i] = c;
		}
		else
		{
			str[i] = 0;
			i++;
			ok = true;
			break;
		}
	}

	if (ok == false)
	{
		return 0;
	}

	return i;
}