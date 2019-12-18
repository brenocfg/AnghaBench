#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct pingpong {long response_time; int /*<<< orphan*/  response; struct connectdata* conn; } ;
struct connectdata {int /*<<< orphan*/  now; struct Curl_easy* data; } ;
struct TYPE_2__ {long server_response_timeout; scalar_t__ timeout; } ;
struct Curl_easy {TYPE_1__ set; } ;

/* Variables and functions */
 scalar_t__ CURLMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Curl_now () ; 
 scalar_t__ Curl_timediff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

time_t Curl_pp_state_timeout(struct pingpong *pp, bool disconnecting)
{
  struct connectdata *conn = pp->conn;
  struct Curl_easy *data = conn->data;
  time_t timeout_ms; /* in milliseconds */
  long response_time = (data->set.server_response_timeout)?
    data->set.server_response_timeout: pp->response_time;

  /* if CURLOPT_SERVER_RESPONSE_TIMEOUT is set, use that to determine
     remaining time, or use pp->response because SERVER_RESPONSE_TIMEOUT is
     supposed to govern the response for any given server response, not for
     the time from connect to the given server response. */

  /* Without a requested timeout, we only wait 'response_time' seconds for the
     full response to arrive before we bail out */
  timeout_ms = response_time -
    (time_t)Curl_timediff(Curl_now(), pp->response); /* spent time */

  if(data->set.timeout && !disconnecting) {
    /* if timeout is requested, find out how much remaining time we have */
    time_t timeout2_ms = data->set.timeout - /* timeout time */
      (time_t)Curl_timediff(Curl_now(), conn->now); /* spent time */

    /* pick the lowest number */
    timeout_ms = CURLMIN(timeout_ms, timeout2_ms);
  }

  return timeout_ms;
}