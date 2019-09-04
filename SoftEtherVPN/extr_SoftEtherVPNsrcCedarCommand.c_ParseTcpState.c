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

/* Variables and functions */
 int IsEmptyStr (char*) ; 
 scalar_t__ StartWith (char*,char*) ; 

bool ParseTcpState(char *src, bool *check_tcp_state, bool *established)
{
	bool ok = false;
	// Validate arguments
	if(src == NULL)
	{
		return false;
	}

	if(check_tcp_state != NULL && established != NULL)
	{
		ok = true;
	}

	if (IsEmptyStr(src) == false)
	{
		if (StartWith("Established", src) == 0)
		{
			if(ok != false)
			{
				*check_tcp_state = true;
				*established = true;
			}
		}
		else if (StartWith("Unestablished", src) == 0)
		{
			if(ok != false)
			{
				*check_tcp_state = true;
				*established = false;
			}
		}
		else
		{
			// Illegal string
			return false;
		}
	}
	else
	{
		if(ok != false)
		{
			*check_tcp_state = false;
			*established = false;
		}
	}

	return true;
}