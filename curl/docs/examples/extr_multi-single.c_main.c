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
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLM_OK ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 int /*<<< orphan*/  WAITMS (int) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ curl_multi_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *http_handle;
  CURLM *multi_handle;

  int still_running = 0; /* keep number of running handles */
  int repeats = 0;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  http_handle = curl_easy_init();

  /* set the options (I left out a few, you'll get the point anyway) */
  curl_easy_setopt(http_handle, CURLOPT_URL, "https://www.example.com/");

  /* init a multi stack */
  multi_handle = curl_multi_init();

  /* add the individual transfers */
  curl_multi_add_handle(multi_handle, http_handle);

  /* we start some action by calling perform right away */
  curl_multi_perform(multi_handle, &still_running);

  while(still_running) {
    CURLMcode mc; /* curl_multi_wait() return code */
    int numfds;

    /* wait for activity, timeout or "nothing" */
    mc = curl_multi_wait(multi_handle, NULL, 0, 1000, &numfds);

    if(mc != CURLM_OK) {
      fprintf(stderr, "curl_multi_wait() failed, code %d.\n", mc);
      break;
    }

    /* 'numfds' being zero means either a timeout or no file descriptors to
       wait for. Try timeout on first occurrence, then assume no file
       descriptors and no file descriptors to wait for means wait for 100
       milliseconds. */

    if(!numfds) {
      repeats++; /* count number of repeated zero numfds */
      if(repeats > 1) {
        WAITMS(100); /* sleep 100 milliseconds */
      }
    }
    else
      repeats = 0;

    curl_multi_perform(multi_handle, &still_running);
  }

  curl_multi_remove_handle(multi_handle, http_handle);

  curl_easy_cleanup(http_handle);

  curl_multi_cleanup(multi_handle);

  curl_global_cleanup();

  return 0;
}