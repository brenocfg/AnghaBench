#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sg_flags; int /*<<< orphan*/  c_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  TCSETA ; 
 int /*<<< orphan*/  TIOCSETP ; 
 TYPE_1__ Terminal ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void 
noecho()		/* turn off echoing				*/
{
	int value;

#ifdef SYS5
	Terminal.c_lflag &= ~ECHO;		/* disable echo		*/
	value = ioctl(0, TCSETA, &Terminal);	/* set characteristics	*/
#else
	Terminal.sg_flags &= ~ECHO;		/* disable echo		*/
	value = ioctl(0, TIOCSETP, &Terminal);	/* set characteristics	*/
#endif
}