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
struct TYPE_3__ {int* c_cc; int /*<<< orphan*/  sg_flags; int /*<<< orphan*/  c_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICANON ; 
 int /*<<< orphan*/  ISIG ; 
 char Intr ; 
 int /*<<< orphan*/  RAW ; 
 int /*<<< orphan*/  TCSETA ; 
 int /*<<< orphan*/  TIOCSETP ; 
 TYPE_1__ Terminal ; 
 size_t VEOF ; 
 size_t VEOL ; 
 size_t VINTR ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void 
noraw()			/* set to normal character read mode		*/
{
	int value;

#ifdef SYS5
	Terminal.c_lflag |= ICANON;	/* enable canonical operation	*/
	Terminal.c_lflag |= ISIG;	/* enable signal checking	*/
	Terminal.c_cc[VEOF] = 4;		/* EOF character = 4	*/
	Terminal.c_cc[VEOL] = '\0';	/* EOL = 0		*/
	Terminal.c_cc[VINTR] = Intr;		/* reset interrupt char	*/
	value = ioctl(0, TCSETA, &Terminal);	/* set characteristics	*/
#else
	Terminal.sg_flags &= ~RAW;	/* disable raw mode		*/
	value = ioctl(0, TIOCSETP, &Terminal);	/* set characteristics	*/
/*	old_arg = fcntl(0, F_GETFL, 0);
	value = fcntl(0, F_SETFL, old_arg & ~FNDELAY);*/
#endif
}