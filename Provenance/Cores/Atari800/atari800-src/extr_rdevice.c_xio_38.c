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
struct termios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  DBG_APRINT (char*) ; 
 int /*<<< orphan*/  Devices_ICAX1Z ; 
 int /*<<< orphan*/  PARENB ; 
 int /*<<< orphan*/  PARODD ; 
 int Peek (int /*<<< orphan*/ ) ; 
 scalar_t__ RDevice_serial_enabled ; 
 int /*<<< orphan*/  TCSANOW ; 
 int linefeeds ; 
 int /*<<< orphan*/  rdev_fd ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int translation ; 

__attribute__((used)) static void xio_38(void)
{
  int aux1;
#if defined(R_SERIAL) && !defined(DREAMCAST)
  struct termios options;
#endif /* defined(R_SERIAL) && !defined(DREAMCAST) */

  CPU_regA = 1;
  CPU_regY = 1;
  CPU_ClrN;

  aux1 = Peek(Devices_ICAX1Z);
#if defined(R_SERIAL) && !defined(DREAMCAST)
  if(RDevice_serial_enabled)
  {
    if(aux1 & 0x04)
    { /*Odd Parity*/
      tcgetattr(rdev_fd, &options);
      options.c_cflag |= PARENB;
      options.c_cflag |= PARODD;
      tcsetattr(rdev_fd, TCSANOW, &options);
    }
    else if(aux1 & 0x08)
    { /*Even Parity*/
      tcgetattr(rdev_fd, &options);
      options.c_cflag |= PARENB;
      options.c_cflag &= ~PARODD;
      tcsetattr(rdev_fd, TCSANOW, &options);

    }
    else
    { /*No Parity*/
      tcgetattr(rdev_fd, &options);
      options.c_cflag &= ~PARENB;
      tcsetattr(rdev_fd, TCSANOW, &options);
    }
  }
#endif /* defined(R_SERIAL) && !defined(DREAMCAST) */

  if(aux1 & 0x20)
  { /* No Translation */
    DBG_APRINT("R*: No ATASCII/ASCII TRANSLATION");
    translation = 0;
  }
  else
  {
    translation = 1;
  }

  if(aux1 & 0x40)
  { /* Append line feed */
    DBG_APRINT("R*: Append Line Feeds");
    linefeeds = 1;
  }
  else
  {
    linefeeds = 0;
  }

}