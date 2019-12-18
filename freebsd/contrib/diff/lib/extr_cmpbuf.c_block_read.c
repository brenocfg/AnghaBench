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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 size_t INT_MAX ; 
 size_t MIN (int,size_t) ; 
 int /*<<< orphan*/  SA_RESTART ; 
 size_t SIZE_MAX ; 
 size_t SSIZE_MAX ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,char*,size_t) ; 

size_t
block_read (int fd, char *buf, size_t nbytes)
{
  char *bp = buf;
  char const *buflim = buf + nbytes;
  size_t readlim = SSIZE_MAX;

  do
    {
      size_t bytes_to_read = MIN (buflim - bp, readlim);
      ssize_t nread = read (fd, bp, bytes_to_read);
      if (nread <= 0)
	{
	  if (nread == 0)
	    break;

	  /* Accommodate Tru64 5.1, which can't read more than INT_MAX
	     bytes at a time.  They call that a 64-bit OS?  */
	  if (errno == EINVAL && INT_MAX < bytes_to_read)
	    {
	      readlim = INT_MAX;
	      continue;
	    }

	  /* This is needed for programs that have signal handlers on
	     older hosts without SA_RESTART.  It also accommodates
	     ancient AIX hosts that set errno to EINTR after uncaught
	     SIGCONT.  See <news:1r77ojINN85n@ftp.UU.NET>
	     (1993-04-22).  */
	  if (! SA_RESTART && errno == EINTR)
	    continue;

	  return SIZE_MAX;
	}
      bp += nread;
    }
  while (bp < buflim);

  return bp - buf;
}