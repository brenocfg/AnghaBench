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
 int /*<<< orphan*/  FLUSHO ; 
 int /*<<< orphan*/  ICANON ; 
 int /*<<< orphan*/  IEXTEN ; 
 int /*<<< orphan*/  ISIG ; 
 int Intr ; 
 int /*<<< orphan*/  PENDIN ; 
 int /*<<< orphan*/  RAW ; 
 int /*<<< orphan*/  TCSETA ; 
 int /*<<< orphan*/  TIOCSETP ; 
 TYPE_1__ Terminal ; 
 size_t VINTR ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void 
raw()			/* set to read characters immediately		*/
{
	int value;

#ifdef SYS5
	Intr = Terminal.c_cc[VINTR];	/* get the interrupt character	*/
	Terminal.c_lflag &= ~ICANON;	/* disable canonical operation	*/
	Terminal.c_lflag &= ~ISIG;	/* disable signal checking	*/
#ifdef FLUSHO
	Terminal.c_lflag &= ~FLUSHO;
#endif
#ifdef PENDIN
	Terminal.c_lflag &= ~PENDIN;
#endif
#ifdef IEXTEN
	Terminal.c_lflag &= ~IEXTEN;
#endif
	Terminal.c_cc[VMIN] = 1;		/* minimum of one character */
	Terminal.c_cc[VTIME] = 0;		/* timeout value	*/
	Terminal.c_cc[VINTR] = 0;		/* eliminate interrupt	*/
	value = ioctl(0, TCSETA, &Terminal);	/* set characteristics	*/
#else
	Terminal.sg_flags |= RAW;	/* enable raw mode		*/
	value = ioctl(0, TIOCSETP, &Terminal);	/* set characteristics	*/
#endif
}