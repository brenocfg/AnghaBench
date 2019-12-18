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
 int /*<<< orphan*/  Saved_tty ; 
 int /*<<< orphan*/  TCSETA ; 
 int /*<<< orphan*/  TIOCSETP ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
resetty()		/* restore previous tty stats			*/
{
	int value;

#ifdef SYS5
	value = ioctl(0, TCSETA, &Saved_tty);	/* set characteristics	*/
#else
	value = ioctl(0, TIOCSETP, &Saved_tty);	/* set characteristics	*/
#endif
}