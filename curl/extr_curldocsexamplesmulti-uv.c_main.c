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
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  add_download (char*,int) ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_handle ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_socket ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  start_timeout ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
  loop = uv_default_loop();

  if(argc <= 1)
    return 0;

  if(curl_global_init(CURL_GLOBAL_ALL)) {
    fprintf(stderr, "Could not init curl\n");
    return 1;
  }

  uv_timer_init(loop, &timeout);

  curl_handle = curl_multi_init();
  curl_multi_setopt(curl_handle, CURLMOPT_SOCKETFUNCTION, handle_socket);
  curl_multi_setopt(curl_handle, CURLMOPT_TIMERFUNCTION, start_timeout);

  while(argc-- > 1) {
    add_download(argv[argc], argc);
  }

  uv_run(loop, UV_RUN_DEFAULT);
  curl_multi_cleanup(curl_handle);

  return 0;
}