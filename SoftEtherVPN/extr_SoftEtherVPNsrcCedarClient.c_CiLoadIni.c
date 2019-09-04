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
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_CUSTOM_INI_FILENAME ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ReadIni (int /*<<< orphan*/ *) ; 

LIST *CiLoadIni()
{
	BUF *b = ReadDump(CLIENT_CUSTOM_INI_FILENAME);
	LIST *ini;
	if (b == NULL)
	{
		return NULL;
	}

	ini = ReadIni(b);

	FreeBuf(b);

	return ini;

}