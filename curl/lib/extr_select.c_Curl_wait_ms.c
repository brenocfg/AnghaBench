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
struct curltime {int dummy; } ;

/* Variables and functions */
 struct curltime Curl_now () ; 
 int /*<<< orphan*/  EINVAL ; 
 int ELAPSED_MS () ; 
 scalar_t__ ERROR_NOT_EINTR (int) ; 
 int /*<<< orphan*/  SET_SOCKERRNO (int /*<<< orphan*/ ) ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int Curl_wait_ms(int timeout_ms)
{
#if !defined(MSDOS) && !defined(USE_WINSOCK)
#ifndef HAVE_POLL_FINE
  struct timeval pending_tv;
#endif
  struct curltime initial_tv;
  int pending_ms;
#endif
  int r = 0;

  if(!timeout_ms)
    return 0;
  if(timeout_ms < 0) {
    SET_SOCKERRNO(EINVAL);
    return -1;
  }
#if defined(MSDOS)
  delay(timeout_ms);
#elif defined(USE_WINSOCK)
  Sleep(timeout_ms);
#else
  pending_ms = timeout_ms;
  initial_tv = Curl_now();
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
    error = SOCKERRNO;
    if(error && ERROR_NOT_EINTR(error))
      break;
    pending_ms = timeout_ms - ELAPSED_MS();
    if(pending_ms <= 0) {
      r = 0;  /* Simulate a "call timed out" case */
      break;
    }
  } while(r == -1);
#endif /* USE_WINSOCK */
  if(r)
    r = -1;
  return r;
}