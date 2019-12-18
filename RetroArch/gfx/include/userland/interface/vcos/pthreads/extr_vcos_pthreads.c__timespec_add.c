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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ NSEC_IN_SEC ; 

__attribute__((used)) static void _timespec_add(struct timespec *left, struct timespec *right)
{
   left->tv_sec += right->tv_sec;
   left->tv_nsec += right->tv_nsec;
   if (left->tv_nsec >= (NSEC_IN_SEC))
   {
      left->tv_nsec -= NSEC_IN_SEC;
      left->tv_sec++;
   }
}