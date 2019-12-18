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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SET_SOCKERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (scalar_t__) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int select_wrapper(int nfds, fd_set *rd, fd_set *wr, fd_set *exc,
                   struct timeval *tv)
{
  if(nfds < 0) {
    SET_SOCKERRNO(EINVAL);
    return -1;
  }
#ifdef USE_WINSOCK
  /*
   * Winsock select() requires that at least one of the three fd_set
   * pointers is not NULL and points to a non-empty fdset. IOW Winsock
   * select() can not be used to sleep without a single fd_set.
   */
  if(!nfds) {
    Sleep((1000*tv->tv_sec) + (DWORD)(((double)tv->tv_usec)/1000.0));
    return 0;
  }
#endif
  return select(nfds, rd, wr, exc, tv);
}