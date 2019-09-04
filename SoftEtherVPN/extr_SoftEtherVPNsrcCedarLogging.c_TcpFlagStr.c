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
typedef  int /*<<< orphan*/  tmp ;
typedef  int UCHAR ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 int TCP_ACK ; 
 int TCP_FIN ; 
 int TCP_PSH ; 
 int TCP_RST ; 
 int TCP_SYN ; 
 int TCP_URG ; 

char *TcpFlagStr(UCHAR flag)
{
	char tmp[MAX_SIZE];
	StrCpy(tmp, sizeof(tmp), "");

	if (flag & TCP_FIN)
	{
		StrCat(tmp, sizeof(tmp), "FIN+");
	}

	if (flag & TCP_SYN)
	{
		StrCat(tmp, sizeof(tmp), "SYN+");
	}

	if (flag & TCP_RST)
	{
		StrCat(tmp, sizeof(tmp), "RST+");
	}

	if (flag & TCP_PSH)
	{
		StrCat(tmp, sizeof(tmp), "PSH+");
	}

	if (flag & TCP_ACK)
	{
		StrCat(tmp, sizeof(tmp), "ACK+");
	}

	if (flag & TCP_URG)
	{
		StrCat(tmp, sizeof(tmp), "URG+");
	}

	if (StrLen(tmp) >= 1)
	{
		if (tmp[StrLen(tmp) - 1] == '+')
		{
			tmp[StrLen(tmp) - 1] = 0;
		}
	}

	return CopyStr(tmp);
}