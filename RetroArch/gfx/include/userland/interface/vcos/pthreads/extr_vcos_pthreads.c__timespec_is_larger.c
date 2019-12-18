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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */

__attribute__((used)) static int _timespec_is_larger(struct timespec *left, struct timespec *right)
{
   if (left->tv_sec != right->tv_sec)
      return left->tv_sec > right->tv_sec;
   else
      return left->tv_nsec > right->tv_nsec;
}