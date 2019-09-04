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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,char*,int) ; 

void CfgAddLine(BUF *b, char *str, UINT depth)
{
	UINT i;
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	for (i = 0;i < depth;i++)
	{
		WriteBuf(b, "\t", 1);
	}
	WriteBuf(b, str, StrLen(str));
	WriteBuf(b, "\r\n", 2);
}