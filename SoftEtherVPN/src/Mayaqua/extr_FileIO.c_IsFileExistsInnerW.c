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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenInnerW (int /*<<< orphan*/ *,int,int) ; 

bool IsFileExistsInnerW(wchar_t *name)
{
	IO *o;
	// Validate arguments
	if (name == NULL)
	{
		return false;
	}

	o = FileOpenInnerW(name, false, false);
	if (o == NULL)
	{
		return false;
	}

	FileClose(o);

	return true;
}