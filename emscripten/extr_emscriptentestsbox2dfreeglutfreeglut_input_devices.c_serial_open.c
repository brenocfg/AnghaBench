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
typedef  int /*<<< orphan*/  termio ;
struct termios {int fd; int c_cflag; int c_iflag; int* c_cc; int /*<<< orphan*/  termio_save; } ;
typedef  struct termios SERIALPORT ;

/* Variables and functions */
 int /*<<< orphan*/  B9600 ; 
 int CREAD ; 
 int CS8 ; 
 int HUPCL ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 struct termios* malloc (int) ; 
 int /*<<< orphan*/  memset (struct termios*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  serial_flush (struct termios*) ; 
 int /*<<< orphan*/  tcgetattr (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static SERIALPORT *serial_open ( const char *device )
{
    int fd;
    struct termios termio;
    SERIALPORT *port;

    fd = open(device, O_RDWR | O_NONBLOCK );
    if (fd <0) {
        perror(device);
        return NULL;
    }

    port = malloc(sizeof(SERIALPORT));
    memset(port, 0, sizeof(SERIALPORT));
    port->fd = fd;

    /* save current port settings */
    tcgetattr(fd,&port->termio_save);

    memset(&termio, 0, sizeof(termio));
    termio.c_cflag = CS8 | CREAD | HUPCL ;
    termio.c_iflag = IGNPAR | IGNBRK ;
    termio.c_cc[VTIME]    = 0;   /* inter-character timer */
    termio.c_cc[VMIN]     = 1;   /* block read until 1 chars received, when blocking I/O */

    cfsetispeed(&termio, B9600);
    cfsetospeed(&termio, B9600);
    tcsetattr(fd,TCSANOW,&termio);

    serial_flush(port);
    return port;
}