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
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgFolderToBufBin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgFolderToBufTextEx (int /*<<< orphan*/ *,int) ; 

BUF *CfgFolderToBufEx(FOLDER *f, bool textmode, bool no_banner)
{
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	if (textmode)
	{
		return CfgFolderToBufTextEx(f, no_banner);
	}
	else
	{
		return CfgFolderToBufBin(f);;
	}
}