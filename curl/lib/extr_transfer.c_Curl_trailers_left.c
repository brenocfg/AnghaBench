#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t trailers_bytes_sent; TYPE_2__* trailers_buf; } ;
struct Curl_easy {TYPE_1__ state; } ;
struct TYPE_4__ {size_t size_used; } ;
typedef  TYPE_2__ Curl_send_buffer ;

/* Variables and functions */

__attribute__((used)) static size_t Curl_trailers_left(void *raw)
{
  struct Curl_easy *data = (struct Curl_easy *)raw;
  Curl_send_buffer *trailers_buf = data->state.trailers_buf;
  return trailers_buf->size_used - data->state.trailers_bytes_sent;
}