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
typedef  int timediff_t ;
struct curltime {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  t_startop; int /*<<< orphan*/  t_startsingle; } ;
struct TYPE_3__ {scalar_t__ timeout; scalar_t__ connecttimeout; } ;
struct Curl_easy {TYPE_2__ progress; TYPE_1__ set; } ;

/* Variables and functions */
 struct curltime Curl_now () ; 
 int Curl_timediff (struct curltime,int /*<<< orphan*/ ) ; 
 int DEFAULT_CONNECT_TIMEOUT ; 

timediff_t Curl_timeleft(struct Curl_easy *data,
                         struct curltime *nowp,
                         bool duringconnect)
{
  int timeout_set = 0;
  timediff_t timeout_ms = duringconnect?DEFAULT_CONNECT_TIMEOUT:0;
  struct curltime now;

  /* if a timeout is set, use the most restrictive one */

  if(data->set.timeout > 0)
    timeout_set |= 1;
  if(duringconnect && (data->set.connecttimeout > 0))
    timeout_set |= 2;

  switch(timeout_set) {
  case 1:
    timeout_ms = data->set.timeout;
    break;
  case 2:
    timeout_ms = data->set.connecttimeout;
    break;
  case 3:
    if(data->set.timeout < data->set.connecttimeout)
      timeout_ms = data->set.timeout;
    else
      timeout_ms = data->set.connecttimeout;
    break;
  default:
    /* use the default */
    if(!duringconnect)
      /* if we're not during connect, there's no default timeout so if we're
         at zero we better just return zero and not make it a negative number
         by the math below */
      return 0;
    break;
  }

  if(!nowp) {
    now = Curl_now();
    nowp = &now;
  }

  /* subtract elapsed time */
  if(duringconnect)
    /* since this most recent connect started */
    timeout_ms -= Curl_timediff(*nowp, data->progress.t_startsingle);
  else
    /* since the entire operation started */
    timeout_ms -= Curl_timediff(*nowp, data->progress.t_startop);
  if(!timeout_ms)
    /* avoid returning 0 as that means no timeout! */
    return -1;

  return timeout_ms;
}