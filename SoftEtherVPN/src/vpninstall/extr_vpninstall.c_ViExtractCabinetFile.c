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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int DumpBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT_RCDATA ; 
 int /*<<< orphan*/ * ViExtractResource (char*,int /*<<< orphan*/ ,char*) ; 

bool ViExtractCabinetFile(char *exe, char *cab)
{
	BUF *b;
	// Validate arguments
	if (exe == NULL || cab == NULL)
	{
		return false;
	}

	b = ViExtractResource(exe, RT_RCDATA, "CABINET");
	if (b == NULL)
	{
		return false;
	}

	if (DumpBuf(b, cab) == false)
	{
		FreeBuf(b);

		return false;
	}

	FreeBuf(b);

	return true;
}