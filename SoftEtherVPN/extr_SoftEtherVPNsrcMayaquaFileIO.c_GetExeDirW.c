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

/* Variables and functions */
 int /*<<< orphan*/  GetDirNameFromFilePathW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exe_file_name_w ; 

void GetExeDirW(wchar_t *name, UINT size)
{
	// Validate arguments
	if (name == NULL)
	{
		return;
	}

	GetDirNameFromFilePathW(name, size, exe_file_name_w);
}