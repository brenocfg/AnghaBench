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
 int /*<<< orphan*/  CURLMOPT_SOCKETFUNCTION ; 
 int /*<<< orphan*/  CURLMOPT_TIMERFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  add_download (char*,int) ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_handle ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_new () ; 
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtimer_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_socket ; 
 int /*<<< orphan*/  libevent_global_shutdown () ; 
 int /*<<< orphan*/  on_timeout ; 
 int /*<<< orphan*/  start_timeout ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timeout ; 

int main(int argc, char **argv)
{
  if(argc <= 1)
    return 0;

  if(curl_global_init(CURL_GLOBAL_ALL)) {
    fprintf(stderr, "Could not init curl\n");
    return 1;
  }

  base = event_base_new();
  timeout = evtimer_new(base, on_timeout, NULL);

  curl_handle = curl_multi_init();
  curl_multi_setopt(curl_handle, CURLMOPT_SOCKETFUNCTION, handle_socket);
  curl_multi_setopt(curl_handle, CURLMOPT_TIMERFUNCTION, start_timeout);

  while(argc-- > 1) {
    add_download(argv[argc], argc);
  }

  event_base_dispatch(base);

  curl_multi_cleanup(curl_handle);
  event_free(timeout);
  event_base_free(base);

  libevent_global_shutdown();
  curl_global_cleanup();

  return 0;
}