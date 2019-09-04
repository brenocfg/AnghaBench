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
 int /*<<< orphan*/  CfgOutputFolderText (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_CPYRIGHT ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BUF *CfgFolderToBufTextEx(FOLDER *f, bool no_banner)
{
	BUF *b;
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	// Create a stream
	b = NewBuf();

	// Copyright notice
	if (no_banner == false)
	{
		WriteBuf(b, TAG_CPYRIGHT, StrLen(TAG_CPYRIGHT));
	}

	// Output the root folder (recursive)
	CfgOutputFolderText(b, f, 0);

	return b;
}