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
struct curltime {int /*<<< orphan*/  tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {TYPE_1__ t_startsingle; } ;
struct Curl_easy {TYPE_2__ progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_pgrsTime (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_STARTSINGLE ; 

__attribute__((used)) static void fake_t_startsingle_time(struct Curl_easy *data,
                                    struct curltime fake_now,
                                    int seconds_offset)
{
  Curl_pgrsTime(data, TIMER_STARTSINGLE);
  data->progress.t_startsingle.tv_sec = fake_now.tv_sec + seconds_offset;
  data->progress.t_startsingle.tv_usec = fake_now.tv_usec;
}