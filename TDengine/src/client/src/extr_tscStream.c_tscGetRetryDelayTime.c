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
typedef  int int64_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ TSDB_TIME_PRECISION_MICRO ; 
 int rand () ; 
 int tsStreamCompRetryDelay ; 

__attribute__((used)) static int64_t tscGetRetryDelayTime(int64_t slidingTime, int16_t prec) {
  float retryRangeFactor = 0.3;

  // change to ms
  if (prec == TSDB_TIME_PRECISION_MICRO) {
    slidingTime = slidingTime / 1000;
  }

  int64_t retryDelta = (int64_t)tsStreamCompRetryDelay * retryRangeFactor;
  retryDelta = ((rand() % retryDelta) + tsStreamCompRetryDelay) * 1000L;

  if (slidingTime < retryDelta) {
    return slidingTime;
  } else {
    return retryDelta;
  }
}