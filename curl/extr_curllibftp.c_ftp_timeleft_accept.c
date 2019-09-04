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
typedef  scalar_t__ timediff_t ;
struct curltime {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  t_acceptdata; } ;
struct TYPE_4__ {scalar_t__ accepttimeout; } ;
struct Curl_easy {TYPE_1__ progress; TYPE_2__ set; } ;

/* Variables and functions */
 struct curltime Curl_now () ; 
 scalar_t__ Curl_timediff (struct curltime,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_timeleft (struct Curl_easy*,struct curltime*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEFAULT_ACCEPT_TIMEOUT ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static timediff_t ftp_timeleft_accept(struct Curl_easy *data)
{
  timediff_t timeout_ms = DEFAULT_ACCEPT_TIMEOUT;
  timediff_t other;
  struct curltime now;

  if(data->set.accepttimeout > 0)
    timeout_ms = data->set.accepttimeout;

  now = Curl_now();

  /* check if the generic timeout possibly is set shorter */
  other =  Curl_timeleft(data, &now, FALSE);
  if(other && (other < timeout_ms))
    /* note that this also works fine for when other happens to be negative
       due to it already having elapsed */
    timeout_ms = other;
  else {
    /* subtract elapsed time */
    timeout_ms -= Curl_timediff(now, data->progress.t_acceptdata);
    if(!timeout_ms)
      /* avoid returning 0 as that means no timeout! */
      return -1;
  }

  return timeout_ms;
}