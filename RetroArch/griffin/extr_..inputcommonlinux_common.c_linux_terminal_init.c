#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int c_lflag; int c_iflag; scalar_t__* c_cc; } ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int ICRNL ; 
 int IGNCR ; 
 int INLCR ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  KDGKBMODE ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 size_t VMIN ; 
 size_t VTIME ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__ newTerm ; 
 int oldKbmd ; 
 TYPE_1__ oldTerm ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

bool linux_terminal_init(void)
{
   if (oldKbmd != 0xffff)
      return false;

   if (tcgetattr(0, &oldTerm) < 0)
      return false;

   newTerm              = oldTerm;
   newTerm.c_lflag     &= ~(ECHO | ICANON | ISIG);
   newTerm.c_iflag     &= ~(ISTRIP | IGNCR | ICRNL | INLCR | IXOFF | IXON);
   newTerm.c_cc[VMIN]   = 0;
   newTerm.c_cc[VTIME]  = 0;

   /* Be careful about recovering the terminal. */
   if (ioctl(0, KDGKBMODE, &oldKbmd) < 0)
      return false;

   if (tcsetattr(0, TCSAFLUSH, &newTerm) < 0)
      return false;

   return true;
}