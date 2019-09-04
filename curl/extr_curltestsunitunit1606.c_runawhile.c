#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct curltime {int member_0; int tv_sec; int /*<<< orphan*/  member_1; } ;
typedef  int curl_off_t ;
struct TYPE_6__ {int current_speed; } ;
struct TYPE_7__ {TYPE_1__ progress; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_LOW_SPEED_LIMIT ; 
 int /*<<< orphan*/  CURLOPT_LOW_SPEED_TIME ; 
 scalar_t__ Curl_speedcheck (TYPE_2__*,struct curltime) ; 
 int /*<<< orphan*/  Curl_speedinit (TYPE_2__*) ; 
 int /*<<< orphan*/  curl_easy_setopt (TYPE_2__*,int /*<<< orphan*/ ,long) ; 
 TYPE_2__* easy ; 

__attribute__((used)) static int runawhile(long time_limit,
                     long speed_limit,
                     curl_off_t speed,
                     int dec)
{
  int counter = 1;
  struct curltime now = {1, 0};
  CURLcode result;
  int finaltime;

  curl_easy_setopt(easy, CURLOPT_LOW_SPEED_LIMIT, speed_limit);
  curl_easy_setopt(easy, CURLOPT_LOW_SPEED_TIME, time_limit);
  Curl_speedinit(easy);

  do {
    /* fake the current transfer speed */
    easy->progress.current_speed = speed;
    result = Curl_speedcheck(easy, now);
    if(result)
      break;
    /* step the time */
    now.tv_sec = ++counter;
    speed -= dec;
  } while(counter < 100);

  finaltime = (int)(now.tv_sec - 1);

  return finaltime;
}