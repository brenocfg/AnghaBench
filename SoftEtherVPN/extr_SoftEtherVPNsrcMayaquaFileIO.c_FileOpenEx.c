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
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/ * FileOpenExW (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 

IO *FileOpenEx(char *name, bool write_mode, bool read_lock)
{
	wchar_t *name_w = CopyStrToUni(name);
	IO *ret = FileOpenExW(name_w, write_mode, read_lock);

	Free(name_w);

	return ret;
}