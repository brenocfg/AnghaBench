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
 void* Malloc (int /*<<< orphan*/ ) ; 

void *SetConsoleRaw()
{
#ifdef	OS_UNIX
	struct termios t, *ret;

	Zero(&t, sizeof(t));
	if (tcgetattr(0, &t) != 0)
	{
		// Failed
		return NULL;
	}

	// Copy the current settings
	ret = Clone(&t, sizeof(t));

	// Change the settings
	t.c_lflag &= (~ICANON);
	t.c_lflag &= (~ECHO);
	t.c_cc[VTIME] = 0;
	t.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &t);

	return ret;
#else	// OS_UNIX
	return Malloc(0);
#endif	// OS_UNIX
}