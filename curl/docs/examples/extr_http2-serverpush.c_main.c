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
struct timeval {int tv_sec; long tv_usec; int member_1; int /*<<< orphan*/  member_0; } ;
struct CURLMsg {scalar_t__ msg; int /*<<< orphan*/ * easy_handle; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_PIPELINING ; 
 int /*<<< orphan*/  CURLMOPT_PUSHDATA ; 
 int /*<<< orphan*/  CURLMOPT_PUSHFUNCTION ; 
 scalar_t__ CURLMSG_DONE ; 
 scalar_t__ CURLM_OK ; 
 int* CURLPIPE_MULTIPLEX ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 struct CURLMsg* curl_multi_info_read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  curl_multi_timeout (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int* server_push_callback ; 
 scalar_t__ setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *easy;
  CURLM *multi_handle;
  int still_running; /* keep number of running handles */
  int transfers = 1; /* we start with one */
  struct CURLMsg *m;

  /* init a multi stack */
  multi_handle = curl_multi_init();

  easy = curl_easy_init();

  /* set options */
  if(setup(easy)) {
    fprintf(stderr, "failed\n");
    return 1;
  }

  /* add the easy transfer */
  curl_multi_add_handle(multi_handle, easy);

  curl_multi_setopt(multi_handle, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);
  curl_multi_setopt(multi_handle, CURLMOPT_PUSHFUNCTION, server_push_callback);
  curl_multi_setopt(multi_handle, CURLMOPT_PUSHDATA, &transfers);

  /* we start some action by calling perform right away */
  curl_multi_perform(multi_handle, &still_running);

  do {
    struct timeval timeout;
    int rc; /* select() return code */
    CURLMcode mc; /* curl_multi_fdset() return code */

    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = -1;

    long curl_timeo = -1;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    /* set a suitable timeout to play around with */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    curl_multi_timeout(multi_handle, &curl_timeo);
    if(curl_timeo >= 0) {
      timeout.tv_sec = curl_timeo / 1000;
      if(timeout.tv_sec > 1)
        timeout.tv_sec = 1;
      else
        timeout.tv_usec = (curl_timeo % 1000) * 1000;
    }

    /* get file descriptors from the transfers */
    mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

    if(mc != CURLM_OK) {
      fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
      break;
    }

    /* On success the value of maxfd is guaranteed to be >= -1. We call
       select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
       no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
       to sleep 100ms, which is the minimum suggested value in the
       curl_multi_fdset() doc. */

    if(maxfd == -1) {
#ifdef _WIN32
      Sleep(100);
      rc = 0;
#else
      /* Portable sleep for platforms other than Windows. */
      struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
      rc = select(0, NULL, NULL, NULL, &wait);
#endif
    }
    else {
      /* Note that on some platforms 'timeout' may be modified by select().
         If you need access to the original value save a copy beforehand. */
      rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
    }

    switch(rc) {
    case -1:
      /* select error */
      break;
    case 0:
    default:
      /* timeout or readable/writable sockets */
      curl_multi_perform(multi_handle, &still_running);
      break;
    }

    /*
     * A little caution when doing server push is that libcurl itself has
     * created and added one or more easy handles but we need to clean them up
     * when we are done.
     */

    do {
      int msgq = 0;;
      m = curl_multi_info_read(multi_handle, &msgq);
      if(m && (m->msg == CURLMSG_DONE)) {
        CURL *e = m->easy_handle;
        transfers--;
        curl_multi_remove_handle(multi_handle, e);
        curl_easy_cleanup(e);
      }
    } while(m);

  } while(transfers); /* as long as we have transfers going */

  curl_multi_cleanup(multi_handle);


  return 0;
}