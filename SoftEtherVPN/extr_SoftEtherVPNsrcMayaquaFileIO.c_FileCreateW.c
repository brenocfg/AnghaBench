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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/ * FileCreateInnerW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InnerFilePathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 

IO *FileCreateW(wchar_t *name)
{
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	InnerFilePathW(tmp, sizeof(tmp), name);

	return FileCreateInnerW(tmp);
}