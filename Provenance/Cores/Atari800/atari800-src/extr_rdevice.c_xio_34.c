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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_ICAX1Z ; 
 int MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 scalar_t__ RDevice_serial_enabled ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ connected ; 
 scalar_t__ do_once ; 
 int /*<<< orphan*/  rdev_fd ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void xio_34(void)
{
#ifndef DREAMCAST  /* Dreamcast port doesn't currently support handshake lines */
  int temp;
  /*int fid;*/
#ifdef R_SERIAL
  struct termios options;
#endif /* R_SERIAL */
  /*int status;*/

  /*fid = MEMORY_dGetByte(0x2e) >> 4;*/
  temp = MEMORY_dGetByte(Devices_ICAX1Z);

#ifdef R_SERIAL
  if(RDevice_serial_enabled)
  {
    tcgetattr(rdev_fd, &options);
    /*ioctl(rdev_fd, TIOCMGET, &status);*/
  }
#endif /* R_SERIAL */

  if(temp & 0x80)
  {
    if(temp & 0x40)
    {
      /* turn DTR on */
#ifdef R_SERIAL
      if(RDevice_serial_enabled)
      {
        /*status |= TIOCM_DTR;*/
      }
#endif /* R_SERIAL */
    }
    else
    {
      /*Drop DTR*/
#ifdef R_SERIAL
      if(RDevice_serial_enabled)
      {
        cfsetispeed(&options, B0);
        cfsetospeed(&options, B0);
      }
#endif /* R_SERIAL */

      if(connected != 0)
      {
        close ( rdev_fd );
        connected = 0;
        do_once = 0;
        /*bufend = 0;*/
      }
    }
  }

#ifdef R_SERIAL
  if(RDevice_serial_enabled)
  {
    /* RTS Set/Clear*/
    if(temp & 0x20)
    {
      if(temp & 0x10)
      {
        /*status |= TIOCM_RTS;*/
      }
      else
      {
        /*status &= ~TIOCM_RTS;*/
      }
    }

    if(temp & 0x02)
    {
      if(temp & 0x01)
      {
        /*status |= TIOCM_RTS;*/
      }
      else
      {
        /*status &= ~TIOCM_RTS;*/
      }
    }
  }
#endif /* R_SERIAL */

#ifdef R_SERIAL
  if(RDevice_serial_enabled)
  {
    tcsetattr(rdev_fd, TCSANOW, &options);
    /*ioctl(rdev_fd, TIOCMSET, &status);*/
  }
#endif /* R_SERIAL */
#endif /* not defined DREAMCAST */

  CPU_regA = 1;
  CPU_regY = 1;
  CPU_ClrN;

}