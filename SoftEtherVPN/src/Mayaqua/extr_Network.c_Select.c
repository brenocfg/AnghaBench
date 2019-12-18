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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SOCKSET ;
typedef  int /*<<< orphan*/  CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  UnixSelect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32Select (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void Select(SOCKSET *set, UINT timeout, CANCEL *c1, CANCEL *c2)
{
#ifdef	OS_WIN32
	Win32Select(set, timeout, c1, c2);
#else
	UnixSelect(set, timeout, c1, c2);
#endif	// OS_WIN32
}