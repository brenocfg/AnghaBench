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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  PACKET_LOG_ALL ; 
 int /*<<< orphan*/  PACKET_LOG_HEADER ; 
 int /*<<< orphan*/  PACKET_LOG_NONE ; 
 scalar_t__ StartWith (char*,char*) ; 

UINT StrToPacketLogSaveInfoType(char *str)
{
	UINT ret = INFINITE;
	if (str == NULL)
	{
		return INFINITE;
	}

	if (StartWith("none", str) || IsEmptyStr(str))
	{
		ret = PACKET_LOG_NONE;
	}
	else if (StartWith("header", str))
	{
		ret = PACKET_LOG_HEADER;
	}
	else if (StartWith("full", str) || StartWith("all", str))
	{
		ret = PACKET_LOG_ALL;
	}

	return ret;
}