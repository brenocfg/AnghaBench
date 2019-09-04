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
struct cb_data {size_t remaining_bytes; int paused; scalar_t__ response_received; } ;

/* Variables and functions */
 size_t CURL_READFUNC_PAUSE ; 
 int /*<<< orphan*/  memset (void*,char,size_t) ; 

__attribute__((used)) static size_t read_callback(void *ptr, size_t size, size_t nitems,
                            void *userdata)
{
  struct cb_data *data = (struct cb_data *)userdata;

  /* wait until the server has sent all response headers */
  if(data->response_received) {
    size_t totalsize = nitems * size;

    size_t bytes_to_send = data->remaining_bytes;
    if(bytes_to_send > totalsize) {
      bytes_to_send = totalsize;
    }

    memset(ptr, 'a', bytes_to_send);
    data->remaining_bytes -= bytes_to_send;

    return bytes_to_send;
  }
  else {
    data->paused = 1;
    return CURL_READFUNC_PAUSE;
  }
}