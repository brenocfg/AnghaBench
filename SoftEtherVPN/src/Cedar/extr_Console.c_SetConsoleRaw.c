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
typedef  int /*<<< orphan*/  t ;
typedef  void termios ;

/* Variables and functions */
 void* Clone (void*,int) ; 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ICANON ; 
 void* Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  Zero (void*,int) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

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