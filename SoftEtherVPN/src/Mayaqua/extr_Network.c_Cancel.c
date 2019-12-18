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
typedef  int /*<<< orphan*/  CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  UnixCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32Cancel (int /*<<< orphan*/ *) ; 

void Cancel(CANCEL *c)
{
#ifdef	OS_WIN32
	Win32Cancel(c);
#else
	UnixCancel(c);
#endif
}