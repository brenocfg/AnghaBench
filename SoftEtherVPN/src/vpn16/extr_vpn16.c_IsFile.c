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
typedef  scalar_t__ HFILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HFILE_ERROR ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _lclose (scalar_t__) ; 
 scalar_t__ _lopen (char*,int /*<<< orphan*/ ) ; 

BOOL IsFile(char *name)
{
	HFILE h;
	if (name == NULL)
	{
		return FALSE;
	}

	h = _lopen(name, OF_READ);
	if (h == HFILE_ERROR)
	{
		return FALSE;
	}
	_lclose(h);

	return TRUE;
}