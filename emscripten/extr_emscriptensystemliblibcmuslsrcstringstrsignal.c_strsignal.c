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

/* Variables and functions */
 scalar_t__ LCTRANS_CUR (char const*) ; 
 int _NSIG ; 
 int sigmap (int) ; 
 char* strings ; 

char *strsignal(int signum)
{
	const char *s = strings;

	signum = sigmap(signum);
	if (signum - 1U >= _NSIG-1) signum = 0;

	for (; signum--; s++) for (; *s; s++);

	return (char *)LCTRANS_CUR(s);
}