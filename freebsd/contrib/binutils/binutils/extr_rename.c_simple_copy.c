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

/* Variables and functions */
 int COPY_BUF ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (char const*,int) ; 
 int errno ; 
 int open (char const*,int,...) ; 
 int read (int,char*,int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int
simple_copy (const char *from, const char *to)
{
  int fromfd, tofd, nread;
  int saved;
  char buf[COPY_BUF];

  fromfd = open (from, O_RDONLY | O_BINARY);
  if (fromfd < 0)
    return -1;
#ifdef O_CREAT
  tofd = open (to, O_CREAT | O_WRONLY | O_TRUNC | O_BINARY, 0777);
#else
  tofd = creat (to, 0777);
#endif
  if (tofd < 0)
    {
      saved = errno;
      close (fromfd);
      errno = saved;
      return -1;
    }
  while ((nread = read (fromfd, buf, sizeof buf)) > 0)
    {
      if (write (tofd, buf, nread) != nread)
	{
	  saved = errno;
	  close (fromfd);
	  close (tofd);
	  errno = saved;
	  return -1;
	}
    }
  saved = errno;
  close (fromfd);
  close (tofd);
  if (nread < 0)
    {
      errno = saved;
      return -1;
    }
  return 0;
}