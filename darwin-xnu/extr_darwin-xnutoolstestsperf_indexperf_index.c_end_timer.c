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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

void end_timer(struct timeval *tp) {
  struct timeval tend;
  gettimeofday(&tend, NULL);
  if(tend.tv_usec >= tp->tv_usec) {
    tp->tv_sec = tend.tv_sec - tp->tv_sec;
    tp->tv_usec = tend.tv_usec - tp->tv_usec;
  }
  else {
    tp->tv_sec = tend.tv_sec - tp->tv_sec - 1;
    tp->tv_usec = tend.tv_usec - tp->tv_usec + 1000000;
  }
}