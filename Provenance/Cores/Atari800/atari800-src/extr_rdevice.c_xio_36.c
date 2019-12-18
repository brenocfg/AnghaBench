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
 int /*<<< orphan*/  B110 ; 
 int /*<<< orphan*/  B115200 ; 
 int /*<<< orphan*/  B1200 ; 
 int /*<<< orphan*/  B134 ; 
 int /*<<< orphan*/  B150 ; 
 int /*<<< orphan*/  B19200 ; 
 int /*<<< orphan*/  B230400 ; 
 int /*<<< orphan*/  B2400 ; 
 int /*<<< orphan*/  B300 ; 
 int /*<<< orphan*/  B4800 ; 
 int /*<<< orphan*/  B50 ; 
 int /*<<< orphan*/  B57600 ; 
 int /*<<< orphan*/  B600 ; 
 int /*<<< orphan*/  B75 ; 
 int /*<<< orphan*/  B9600 ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  CS5 ; 
 int /*<<< orphan*/  CS6 ; 
 int /*<<< orphan*/  CS7 ; 
 int /*<<< orphan*/  CS8 ; 
 int /*<<< orphan*/  CSIZE ; 
 int /*<<< orphan*/  CSTOPB ; 
 int /*<<< orphan*/  Devices_ICAX1Z ; 
 int /*<<< orphan*/  Devices_ICAX2Z ; 
 int MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 scalar_t__ RDevice_serial_enabled ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_set_baud (int) ; 
 int /*<<< orphan*/  rdev_fd ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void xio_36(void)
{
  int aux1, aux2;
#if defined(R_SERIAL) && !defined(DREAMCAST)
  struct termios options;
#endif /* defined(R_SERIAL) && !defined(DREAMCAST) */

  aux1 = MEMORY_dGetByte(Devices_ICAX1Z);
  aux2 = MEMORY_dGetByte(Devices_ICAX2Z);

#ifdef R_SERIAL
  if(RDevice_serial_enabled)
  {
#ifndef DREAMCAST
    tcgetattr(rdev_fd, &options);

    /*Set Stop bits*/
    if(aux1 & 0x80)
    { /*2 Stop bits*/
      options.c_cflag |= CSTOPB;
    }
    else
    { /*1 Stop bit*/
      options.c_cflag &= ~CSTOPB;
    }

    /*Set word size*/
    if((aux1 & 0x30) == 0)
    { /*8 bit word size*/
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS8;
    }
    else if((aux1 & 0x30) == 0x10)
    { /*7 bit word size*/
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS7;
    }
    else if((aux1 & 0x30) == 0x20)
    { /*6 bit word size*/
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS6;
    }
    else if((aux1 & 0x30) == 0x30)
    { /*5 bit word size*/
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS5;
    }
    else
    { /*8 bit word size*/
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS8;
    }

    /*Set Baud Rate*/
    if((aux1 & 0x0f) == 0)
    { /*300 Baud*/
      cfsetispeed(&options, B300);
      cfsetospeed(&options, B300);
    }
    else if((aux1 & 0x0f) == 1)
    { /* 45.5 Baud (unsupported) - now 57600 */
#ifdef B57600
      cfsetispeed(&options, B57600);
      cfsetospeed(&options, B57600);
#else
      cfsetispeed(&options, B50);
      cfsetospeed(&options, B50);
#endif
    }
    else if ((aux1 & 0x0f) == 2)
    { /* 50 Baud */
      cfsetispeed(&options, B50);
      cfsetospeed(&options, B50);
    }
    else if ((aux1 & 0x0f) == 3)
    { /* 56.875 Baud (unsupported) - now 115200 */
#ifdef B115200
      cfsetispeed(&options, B115200);
      cfsetospeed(&options, B115200);
#else
      cfsetispeed(&options, B50);
      cfsetospeed(&options, B50);
#endif
    }
    else if((aux1 & 0x0f) == 4)
    { /* 75 Baud */
      cfsetispeed(&options, B75);
      cfsetospeed(&options, B75);
    }
    else if((aux1 & 0x0f) == 5)
    { /* 110 Baud */
      cfsetispeed(&options, B110);
      cfsetospeed(&options, B110);
    }
    else if((aux1 & 0x0f) == 6)
    { /* 134.5 Baud */
      cfsetispeed(&options, B134);
      cfsetospeed(&options, B134);
    }
    else if((aux1 & 0x0f) == 7)
    { /* 150 Baud */
      cfsetispeed(&options, B150);
      cfsetospeed(&options, B150);
    }
    else if((aux1 & 0x0f) == 8)
    { /* 300 Baud */
      cfsetispeed(&options, B300);
      cfsetospeed(&options, B300);
    }
    else if((aux1 & 0x0f) == 9)
    { /* 600 Baud */
      cfsetispeed(&options, B600);
      cfsetospeed(&options, B600);
    }
    else if((aux1 & 0x0f) == 10)
    { /* 1200 Baud */
      cfsetispeed(&options, B1200);
      cfsetospeed(&options, B1200);
    }
    else if((aux1 & 0x0f) == 12)
    { /* 2400 Baud */
      cfsetispeed(&options, B2400);
      cfsetospeed(&options, B2400);
    }
    else if((aux1 & 0x0f) == 13)
    { /* 4800 Baud */
      cfsetispeed(&options, B4800);
      cfsetospeed(&options, B4800);
    }
    else if((aux1 & 0x0f) == 14)
    { /* 9600 Baud */
      cfsetispeed(&options, B9600);
      cfsetospeed(&options, B9600);
    }
    else if((aux1 & 0x0f) == 15)
    { /* 19200 Baud */
#ifdef B19200
      cfsetispeed(&options, B19200);
      cfsetospeed(&options, B19200);
#else
      cfsetispeed(&options, B9600);
      cfsetospeed(&options, B9600);
#endif
    }
    else
    { /* 115200 Baud (can add 38400, 76800 if wanted) */
#ifdef B115200
      cfsetispeed(&options, B115200);
      cfsetospeed(&options, B115200);
#else
      cfsetispeed(&options, B9600);
      cfsetospeed(&options, B9600);
#endif
    }

    if(aux1 & 0x40)
    { /* 230400 Baud */
#ifdef B230400
      cfsetispeed(&options, B230400);
      cfsetospeed(&options, B230400);
#endif
    }

    tcsetattr(rdev_fd, TCSANOW, &options);
#else /* below DREAMCAST, above not; both R_SERIAL */
    /* Set Stop bits */
    if(aux1 & 0x80)
    { /* 2 Stop bits */
      /* currently not supported on DC */
    }
    else
    { /* 1 Stop bit */
      /* currently not supported on DC */
    }

    /* Set word size */
    if((aux1 & 0x30) == 0)
    { /* 8 bit word size */
      /* currently not supported on DC */
    }
    else if((aux1 & 0x30) == 0x10)
    { /* 7 bit word size */
      /* currently not supported on DC */
    }
    else if((aux1 & 0x30) == 0x20)
    { /* 6 bit word size */
      /* currently not supported on DC */
    }
    else if((aux1 & 0x30) == 0x30)
    { /* 5 bit word size */
      /* currently not supported on DC */
    }
    else
    { /* 8 bit word size */
      /* currently not supported on DC */
    }

    /* Set Baud Rate */
    if((aux1 & 0x0f) == 0)
    { /* 300 Baud */
      dc_set_baud(300);
    }
    else if((aux1 & 0x0f) == 1)
    { /* 45.5 Baud (unsupported) - now 57600 */
      dc_set_baud(57600);
    }
    else if ((aux1 & 0x0f) == 2)
    { /* 50 Baud */
      dc_set_baud(50);
    }
    else if ((aux1 & 0x0f) == 3)
    { /* 56.875 Baud (unsupported) - now 115200 */
      dc_set_baud(115200);
    }
    else if((aux1 & 0x0f) == 4)
    { /* 75 Baud */
      dc_set_baud(75);
    }
    else if((aux1 & 0x0f) == 5)
    { /* 110 Baud */
      dc_set_baud(110);
    }
    else if((aux1 & 0x0f) == 6)
    { /* 134.5 Baud */
      dc_set_baud(134);
    }
    else if((aux1 & 0x0f) == 7)
    { /* 150 Baud */
      dc_set_baud(150);
    }
    else if((aux1 & 0x0f) == 8)
    { /* 300 Baud */
      dc_set_baud(300);
    }
    else if((aux1 & 0x0f) == 9)
    { /* 600 Baud */
      dc_set_baud(600);
    }
    else if((aux1 & 0x0f) == 10)
    { /* 1200 Baud */
      dc_set_baud(1200);
    }
    else if((aux1 & 0x0f) == 12)
    { /* 2400 Baud */
      dc_set_baud(2400);
    }
    else if((aux1 & 0x0f) == 13)
    { /* 4800 Baud */
      dc_set_baud(4800);
    }
    else if((aux1 & 0x0f) == 14)
    { /* 9600 Baud */
      dc_set_baud(9600);
    }
    else if((aux1 & 0x0f) == 15)
    { /* 19200 Baud */
      dc_set_baud(19200);
    }
    else
    { /* 115200 Baud (can add 38400, 76800 if wanted) */
      dc_set_baud(115200);
    }

    if(aux1 & 0x40)
    { /*  230400 Baud */
      dc_set_baud(230400);
    }
#endif /* DREAMCAST */
  }
#endif /* R_SERIAL */

  CPU_regA = 1;
  CPU_regY = 1;
  CPU_ClrN;
}