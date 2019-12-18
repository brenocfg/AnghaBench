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

/* Variables and functions */
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Win32GetNicList () ; 

LIST *GetNicList()
{
	LIST *o = NULL;

#ifdef	OS_WIN32
	o = Win32GetNicList();

	if (o != NULL)
	{
		return o;
	}

#endif	// OS_WIN32

	return NewListFast(NULL);
}