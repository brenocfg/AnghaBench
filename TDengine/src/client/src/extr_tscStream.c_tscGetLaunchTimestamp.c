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
typedef  long int64_t ;
struct TYPE_3__ {long stime; scalar_t__ precision; double interval; } ;
typedef  TYPE_1__ SSqlStream ;

/* Variables and functions */
 scalar_t__ TSDB_TIME_PRECISION_MICRO ; 
 long rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 long taosGetTimestamp (scalar_t__) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 long tsMaxStreamComputDelay ; 
 long tsStreamCompStartDelay ; 

__attribute__((used)) static int64_t tscGetLaunchTimestamp(const SSqlStream *pStream) {
  int64_t timer = pStream->stime - taosGetTimestamp(pStream->precision);
  if (timer < 0) timer = 0;

  int64_t delayDelta = (int64_t)(pStream->interval * 0.1);

  int64_t maxDelay =
      (pStream->precision == TSDB_TIME_PRECISION_MICRO) ? tsMaxStreamComputDelay * 1000L : tsMaxStreamComputDelay;
  if (delayDelta > maxDelay) {
    delayDelta = maxDelay;
  }

  int64_t startDelay =
      (pStream->precision == TSDB_TIME_PRECISION_MICRO) ? tsStreamCompStartDelay * 1000L : tsStreamCompStartDelay;

  srand(time(NULL));
  timer += (rand() % delayDelta);  // a random number

  if (timer < startDelay || timer > maxDelay) {
    timer = (timer % startDelay) + startDelay;
  }

  return (pStream->precision == TSDB_TIME_PRECISION_MICRO) ? timer / 1000L : timer;
}