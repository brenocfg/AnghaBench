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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  MSG_OUT (char*,char const*) ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int mkfifo (char const*,int) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

int init_fifo(void)
{
  struct stat st;
  const char *fifo = "hiper.fifo";
  int socket;

  if(lstat (fifo, &st) == 0) {
    if((st.st_mode & S_IFMT) == S_IFREG) {
      errno = EEXIST;
      perror("lstat");
      exit(1);
    }
  }

  unlink(fifo);
  if(mkfifo (fifo, 0600) == -1) {
    perror("mkfifo");
    exit(1);
  }

  socket = open(fifo, O_RDWR | O_NONBLOCK, 0);

  if(socket == -1) {
    perror("open");
    exit(1);
  }
  MSG_OUT("Now, pipe some URL's into > %s\n", fifo);

  return socket;
}