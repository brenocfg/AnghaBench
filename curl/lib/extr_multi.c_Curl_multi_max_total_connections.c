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
struct Curl_multi {size_t max_total_connections; } ;

/* Variables and functions */

size_t Curl_multi_max_total_connections(struct Curl_multi *multi)
{
  return multi ? multi->max_total_connections : 0;
}