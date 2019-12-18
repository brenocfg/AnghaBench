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
struct cb_data {int response_received; int /*<<< orphan*/  easy_handle; scalar_t__ paused; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLPAUSE_CONT ; 
 int /*<<< orphan*/  curl_easy_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t write_callback(char *ptr, size_t size, size_t nmemb,
                             void *userdata)
{
  struct cb_data *data = (struct cb_data *)userdata;
  size_t totalsize = nmemb * size;

  /* unused parameter */
  (void)ptr;

  /* all response headers have been received */
  data->response_received = 1;

  if(data->paused) {
    /* continue to send request body data */
    data->paused = 0;
    curl_easy_pause(data->easy_handle, CURLPAUSE_CONT);
  }

  return totalsize;
}