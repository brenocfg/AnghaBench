#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timediff_t ;
struct curltime {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct Curl_multi {TYPE_1__* timetree; } ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_OK ; 
 struct curltime Curl_now () ; 
 TYPE_1__* Curl_splay (struct curltime,TYPE_1__*) ; 
 scalar_t__ Curl_splaycomparekeys (int /*<<< orphan*/ ,struct curltime) ; 
 scalar_t__ Curl_timediff (int /*<<< orphan*/ ,struct curltime) ; 

__attribute__((used)) static CURLMcode multi_timeout(struct Curl_multi *multi,
                               long *timeout_ms)
{
  static struct curltime tv_zero = {0, 0};

  if(multi->timetree) {
    /* we have a tree of expire times */
    struct curltime now = Curl_now();

    /* splay the lowest to the bottom */
    multi->timetree = Curl_splay(tv_zero, multi->timetree);

    if(Curl_splaycomparekeys(multi->timetree->key, now) > 0) {
      /* some time left before expiration */
      timediff_t diff = Curl_timediff(multi->timetree->key, now);
      if(diff <= 0)
        /*
         * Since we only provide millisecond resolution on the returned value
         * and the diff might be less than one millisecond here, we don't
         * return zero as that may cause short bursts of busyloops on fast
         * processors while the diff is still present but less than one
         * millisecond! instead we return 1 until the time is ripe.
         */
        *timeout_ms = 1;
      else
        /* this should be safe even on 64 bit archs, as we don't use that
           overly long timeouts */
        *timeout_ms = (long)diff;
    }
    else
      /* 0 means immediately */
      *timeout_ms = 0;
  }
  else
    *timeout_ms = -1;

  return CURLM_OK;
}