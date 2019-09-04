#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int timediff_t ;
struct curltime {scalar_t__ tv_sec; } ;
struct TYPE_6__ {int low_speed_time; scalar_t__ low_speed_limit; } ;
struct TYPE_5__ {struct curltime keeps_speed; } ;
struct TYPE_4__ {scalar_t__ current_speed; } ;
struct Curl_easy {TYPE_3__ set; TYPE_2__ state; TYPE_1__ progress; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OPERATION_TIMEDOUT ; 
 int /*<<< orphan*/  Curl_expire (struct Curl_easy*,int,int /*<<< orphan*/ ) ; 
 int Curl_timediff (struct curltime,struct curltime) ; 
 int /*<<< orphan*/  EXPIRE_SPEEDCHECK ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,scalar_t__,int) ; 

CURLcode Curl_speedcheck(struct Curl_easy *data,
                         struct curltime now)
{
  if((data->progress.current_speed >= 0) && data->set.low_speed_time) {
    if(data->progress.current_speed < data->set.low_speed_limit) {
      if(!data->state.keeps_speed.tv_sec)
        /* under the limit at this very moment */
        data->state.keeps_speed = now;
      else {
        /* how long has it been under the limit */
        timediff_t howlong = Curl_timediff(now, data->state.keeps_speed);

        if(howlong >= data->set.low_speed_time * 1000) {
          /* too long */
          failf(data,
                "Operation too slow. "
                "Less than %ld bytes/sec transferred the last %ld seconds",
                data->set.low_speed_limit,
                data->set.low_speed_time);
          return CURLE_OPERATION_TIMEDOUT;
        }
      }
    }
    else
      /* faster right now */
      data->state.keeps_speed.tv_sec = 0;
  }

  if(data->set.low_speed_limit)
    /* if low speed limit is enabled, set the expire timer to make this
       connection's speed get checked again in a second */
    Curl_expire(data, 1000, EXPIRE_SPEEDCHECK);

  return CURLE_OK;
}