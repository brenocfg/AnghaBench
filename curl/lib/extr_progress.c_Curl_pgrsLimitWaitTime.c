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
typedef  int timediff_t ;
typedef  int time_t ;
struct curltime {int dummy; } ;
typedef  int curl_off_t ;

/* Variables and functions */
 int CURL_OFF_T_C (int) ; 
 int CURL_OFF_T_MAX ; 
 int Curl_timediff (struct curltime,struct curltime) ; 
 int TIMEDIFF_T_MAX ; 

timediff_t Curl_pgrsLimitWaitTime(curl_off_t cursize,
                                  curl_off_t startsize,
                                  curl_off_t limit,
                                  struct curltime start,
                                  struct curltime now)
{
  curl_off_t size = cursize - startsize;
  timediff_t minimum;
  timediff_t actual;

  if(!limit || !size)
    return 0;

  /*
   * 'minimum' is the number of milliseconds 'size' should take to download to
   * stay below 'limit'.
   */
  if(size < CURL_OFF_T_MAX/1000)
    minimum = (time_t) (CURL_OFF_T_C(1000) * size / limit);
  else {
    minimum = (time_t) (size / limit);
    if(minimum < TIMEDIFF_T_MAX/1000)
      minimum *= 1000;
    else
      minimum = TIMEDIFF_T_MAX;
  }

  /*
   * 'actual' is the time in milliseconds it took to actually download the
   * last 'size' bytes.
   */
  actual = Curl_timediff(now, start);
  if(actual < minimum) {
    /* if it downloaded the data faster than the limit, make it wait the
       difference */
    return (minimum - actual);
  }

  return 0;
}