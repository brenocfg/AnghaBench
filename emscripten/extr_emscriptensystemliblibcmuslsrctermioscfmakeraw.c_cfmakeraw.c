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
struct termios {int c_iflag; int c_lflag; int c_cflag; int* c_cc; int /*<<< orphan*/  c_oflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CS8 ; 
 int CSIZE ; 
 int ECHO ; 
 int ECHONL ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNCR ; 
 int INLCR ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXON ; 
 int /*<<< orphan*/  OPOST ; 
 int PARENB ; 
 int PARMRK ; 
 size_t VMIN ; 
 size_t VTIME ; 

void cfmakeraw(struct termios *t)
{
	t->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
	t->c_oflag &= ~OPOST;
	t->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
	t->c_cflag &= ~(CSIZE|PARENB);
	t->c_cflag |= CS8;
	t->c_cc[VMIN] = 1;
	t->c_cc[VTIME] = 0;
}