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
typedef  int /*<<< orphan*/  VI_SETTING ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDump (char*) ; 
 int ViLoadInfFromBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool ViLoadInf(VI_SETTING *set, char *filename)
{
	BUF *b;
	bool ret = false;
	// Validate arguments
	if (set == NULL || filename == NULL)
	{
		return false;
	}

	b = ReadDump(filename);
	if (b == NULL)
	{
		return false;
	}

	ret = ViLoadInfFromBuf(set, b);

	FreeBuf(b);

	return ret;
}