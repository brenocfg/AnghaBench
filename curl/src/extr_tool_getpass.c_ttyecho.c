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
struct TYPE_5__ {int /*<<< orphan*/  c_lflag; } ;
typedef  TYPE_1__ struct_term ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO ; 
 int FALSE ; 
 int /*<<< orphan*/  TCGETA ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TCSETA ; 
 int TRUE ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tcgetattr (int,TYPE_1__*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static bool ttyecho(bool enable, int fd)
{
#ifdef struct_term
  static struct_term withecho;
  static struct_term noecho;
#endif
  if(!enable) {
    /* disable echo by extracting the current 'withecho' mode and remove the
       ECHO bit and set back the struct */
#ifdef HAVE_TERMIOS_H
    tcgetattr(fd, &withecho);
    noecho = withecho;
    noecho.c_lflag &= ~ECHO;
    tcsetattr(fd, TCSANOW, &noecho);
#elif defined(HAVE_TERMIO_H)
    ioctl(fd, TCGETA, &withecho);
    noecho = withecho;
    noecho.c_lflag &= ~ECHO;
    ioctl(fd, TCSETA, &noecho);
#else
    /* neither HAVE_TERMIO_H nor HAVE_TERMIOS_H, we can't disable echo! */
    (void)fd;
    return FALSE; /* not disabled */
#endif
    return TRUE; /* disabled */
  }
  /* re-enable echo, assumes we disabled it before (and set the structs we
     now use to reset the terminal status) */
#ifdef HAVE_TERMIOS_H
  tcsetattr(fd, TCSAFLUSH, &withecho);
#elif defined(HAVE_TERMIO_H)
  ioctl(fd, TCSETA, &withecho);
#else
  return FALSE; /* not enabled */
#endif
  return TRUE; /* enabled */
}