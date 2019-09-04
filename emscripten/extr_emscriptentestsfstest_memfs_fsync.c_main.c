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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  REPORT_RESULT (scalar_t__) ; 
 scalar_t__ close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fsync (int) ; 
 int open (char*,int,int) ; 
 scalar_t__ result ; 
 int stat (char*,struct stat*) ; 
 int write (int,char*,int) ; 

int main() {
  int fd;

  // We first make sure the file doesn't currently exist.
  // We then write a file, call fsync, and close the file,
  // to make sure synchronous calls to resume does not throw.

  struct stat st;

  // a file whose contents are just 'az'
  if ((stat("/wakaka.txt", &st) != -1) || (errno != ENOENT))
    result = -1000 - errno;
  fd = open("/wakaka.txt", O_RDWR | O_CREAT, 0666);
  if (fd == -1)
    result = -2000 - errno;
  else
  {
    if (write(fd,"az",2) != 2)
      result = -3000 - errno;

    if (fsync(fd) != 0)
      result = -4000 - errno;

    if (close(fd) != 0)
      result = -5000 - errno;
  }

  REPORT_RESULT(result);
}