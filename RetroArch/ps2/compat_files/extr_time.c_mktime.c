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
typedef  int time_t ;
struct tm {int dummy; } ;

/* Variables and functions */

time_t mktime(struct tm *timeptr)
{
   time_t tim = -1;
   /* TODO: This function need to be implemented again because the SDK one is not working fine */
   return tim;
}