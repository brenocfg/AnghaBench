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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreateW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

bool DumpDataW(void *data, UINT size, wchar_t *filename)
{
	IO *o;
	// Validate arguments
	if (filename == NULL || (size != 0 && data == NULL))
	{
		return false;
	}

	o = FileCreateW(filename);
	if (o == NULL)
	{
		return false;
	}
	FileWrite(o, data, size);
	FileClose(o);

	return true;
}