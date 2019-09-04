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
struct curltime {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

struct curltime Curl_now(void)
{
  /*
  ** time() returns the value of time in seconds since the Epoch.
  */
  struct curltime now;
  now.tv_sec = time(NULL);
  now.tv_usec = 0;
  return now;
}