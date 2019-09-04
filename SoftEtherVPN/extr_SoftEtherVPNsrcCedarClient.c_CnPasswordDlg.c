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
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */

void CnPasswordDlg(SOCK *s, PACK *p)
{
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	Win32CnPasswordDlg(s, p);
#endif	// OS_WIN32
}