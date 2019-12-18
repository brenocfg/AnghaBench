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
struct Curl_multi {scalar_t__ max_concurrent_streams; } ;

/* Variables and functions */

size_t Curl_multi_max_concurrent_streams(struct Curl_multi *multi)
{
  return multi ? ((size_t)multi->max_concurrent_streams ?
                  (size_t)multi->max_concurrent_streams : 100) : 0;
}