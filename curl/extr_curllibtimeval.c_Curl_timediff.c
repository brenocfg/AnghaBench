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
struct curltime {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int TIME_MAX ; 
 int TIME_MIN ; 

timediff_t Curl_timediff(struct curltime newer, struct curltime older)
{
  timediff_t diff = (timediff_t)newer.tv_sec-older.tv_sec;
  if(diff >= (TIME_MAX/1000))
    return TIME_MAX;
  else if(diff <= (TIME_MIN/1000))
    return TIME_MIN;
  return diff * 1000 + (newer.tv_usec-older.tv_usec)/1000;
}