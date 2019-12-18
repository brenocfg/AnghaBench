#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  blocking; int /*<<< orphan*/  filedes; } ;
typedef  TYPE_1__ apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ENOTIMPL ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  BLK_OFF ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_FNDELAY ; 
 int O_NDELAY ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static apr_status_t pipenonblock(apr_file_t *thepipe)
{
#if !defined(BEOS) || !BEOS_BLOCKING
      int fd_flags = fcntl(thepipe->filedes, F_GETFL, 0);

#  if defined(O_NONBLOCK)
      fd_flags |= O_NONBLOCK;
#  elif defined(O_NDELAY)
      fd_flags |= O_NDELAY;
#  elif defined(O_FNDELAY)
      fd_flags |= O_FNDELAY;
#  else
      /* XXXX: this breaks things, but an alternative isn't obvious...*/
      return APR_ENOTIMPL;
#  endif
      if (fcntl(thepipe->filedes, F_SETFL, fd_flags) == -1) {
          return errno;
      }
    
#else /* BEOS_BLOCKING */

#  if BEOS_BONE /* This only works on BONE 0-6 */
      int on = 1;
      if (ioctl(thepipe->filedes, FIONBIO, &on, sizeof(on)) < 0) {
          return errno;
      }
#  else /* "classic" BeOS doesn't support this at all */
      return APR_ENOTIMPL;
#  endif

#endif /* !BEOS_BLOCKING */

    thepipe->blocking = BLK_OFF;
    return APR_SUCCESS;
}