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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int errno ; 
 int poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ timediff (struct timeval,struct timeval) ; 
 struct timeval tvnow () ; 

int wait_ms(int timeout_ms)
{
#if !defined(MSDOS) && !defined(USE_WINSOCK)
#ifndef HAVE_POLL_FINE
  struct timeval pending_tv;
#endif
  struct timeval initial_tv;
  int pending_ms;
#endif
  int r = 0;

  if(!timeout_ms)
    return 0;
  if(timeout_ms < 0) {
    errno = EINVAL;
    return -1;
  }
#if defined(MSDOS)
  delay(timeout_ms);
#elif defined(USE_WINSOCK)
  Sleep(timeout_ms);
#else
  pending_ms = timeout_ms;
  initial_tv = tvnow();
  do {
    int error;
#if defined(HAVE_POLL_FINE)
    r = poll(NULL, 0, pending_ms);
#else
    pending_tv.tv_sec = pending_ms / 1000;
    pending_tv.tv_usec = (pending_ms % 1000) * 1000;
    r = select(0, NULL, NULL, NULL, &pending_tv);
#endif /* HAVE_POLL_FINE */
    if(r != -1)
      break;
    error = errno;
    if(error && (error != EINTR))
      break;
    pending_ms = timeout_ms - (int)timediff(tvnow(), initial_tv);
    if(pending_ms <= 0)
      break;
  } while(r == -1);
#endif /* USE_WINSOCK */
  if(r)
    r = -1;
  return r;
}