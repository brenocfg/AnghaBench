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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 size_t read (int,char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int ttyecho (int /*<<< orphan*/ ,int) ; 

char *getpass_r(const char *prompt, /* prompt to display */
                char *password,     /* buffer to store password in */
                size_t buflen)      /* size of buffer to store password in */
{
  ssize_t nread;
  bool disabled;
  int fd = open("/dev/tty", O_RDONLY);
  if(-1 == fd)
    fd = STDIN_FILENO; /* use stdin if the tty couldn't be used */

  disabled = ttyecho(FALSE, fd); /* disable terminal echo */

  fputs(prompt, stderr);
  nread = read(fd, password, buflen);
  if(nread > 0)
    password[--nread] = '\0'; /* zero terminate where enter is stored */
  else
    password[0] = '\0'; /* got nothing */

  if(disabled) {
    /* if echo actually was disabled, add a newline */
    fputs("\n", stderr);
    (void)ttyecho(TRUE, fd); /* enable echo */
  }

  if(STDIN_FILENO != fd)
    close(fd);

  return password; /* return pointer to buffer */
}