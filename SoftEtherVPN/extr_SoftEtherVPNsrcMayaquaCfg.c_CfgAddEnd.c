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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddLine (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void CfgAddEnd(BUF *b, UINT depth)
{
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	CfgAddLine(b, "}", depth);
//	CfgAddLine(b, TAG_END, depth);
}