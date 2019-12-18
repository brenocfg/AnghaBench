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
 int /*<<< orphan*/ * ReadDump (char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 

BUF *AdminWebTryOneFile(char *filename, char *ret_filename, UINT ret_filename_size)
{
	BUF *b;
	if (filename == NULL || ret_filename == NULL)
	{
		return NULL;
	}

	b = ReadDump(filename);
	if (b == NULL)
	{
		return NULL;
	}

	StrCpy(ret_filename, ret_filename_size, filename);

	return b;
}