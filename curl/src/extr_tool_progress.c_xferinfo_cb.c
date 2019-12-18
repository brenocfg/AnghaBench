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
struct per_transfer {void* ulnow; void* ultotal; void* dlnow; void* dltotal; } ;
typedef  void* curl_off_t ;

/* Variables and functions */

int xferinfo_cb(void *clientp,
                curl_off_t dltotal,
                curl_off_t dlnow,
                curl_off_t ultotal,
                curl_off_t ulnow)
{
  struct per_transfer *per = clientp;
  per->dltotal = dltotal;
  per->dlnow = dlnow;
  per->ultotal = ultotal;
  per->ulnow = ulnow;
  return 0;
}