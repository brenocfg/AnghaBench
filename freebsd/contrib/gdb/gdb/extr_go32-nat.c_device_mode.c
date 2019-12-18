#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ax; int bx; int flags; int dx; } ;
struct TYPE_5__ {TYPE_1__ x; } ;
typedef  TYPE_2__ __dpmi_regs ;

/* Variables and functions */
 int /*<<< orphan*/  __dpmi_int (int,TYPE_2__*) ; 

__attribute__((used)) static int
device_mode (int fd, int raw_p)
{
  int oldmode, newmode;
  __dpmi_regs regs;

  regs.x.ax = 0x4400;
  regs.x.bx = fd;
  __dpmi_int (0x21, &regs);
  if (regs.x.flags & 1)
    return -1;
  newmode = oldmode = regs.x.dx;

  if (raw_p)
    newmode |= 0x20;
  else
    newmode &= ~0x20;

  if (oldmode & 0x80)	/* Only for character dev */
  {
    regs.x.ax = 0x4401;
    regs.x.bx = fd;
    regs.x.dx = newmode & 0xff;   /* Force upper byte zero, else it fails */
    __dpmi_int (0x21, &regs);
    if (regs.x.flags & 1)
      return -1;
  }
  return (oldmode & 0x20) == 0x20;
}