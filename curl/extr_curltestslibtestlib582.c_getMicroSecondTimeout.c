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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int curlx_sztosi (scalar_t__) ; 
 struct timeval tutil_tvnow () ; 

__attribute__((used)) static int getMicroSecondTimeout(struct timeval* timeout)
{
  struct timeval now;
  ssize_t result;
  now = tutil_tvnow();
  result = (ssize_t)((timeout->tv_sec - now.tv_sec) * 1000000 +
    timeout->tv_usec - now.tv_usec);
  if(result < 0)
    result = 0;

  return curlx_sztosi(result);
}