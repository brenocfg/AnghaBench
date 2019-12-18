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
struct timeval {double tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static double timeDiff(struct timeval *pStart, struct timeval *pEnd){
  return (pEnd->tv_usec - pStart->tv_usec)*0.000001 + 
         (double)(pEnd->tv_sec - pStart->tv_sec);
}