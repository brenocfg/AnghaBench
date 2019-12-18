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
struct curl_waitfd {int dummy; } ;
struct Curl_multi {int dummy; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_multi_wait (struct Curl_multi*,struct curl_waitfd*,unsigned int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 

CURLMcode curl_multi_wait(struct Curl_multi *multi,
                          struct curl_waitfd extra_fds[],
                          unsigned int extra_nfds,
                          int timeout_ms,
                          int *ret)
{
  return Curl_multi_wait(multi, extra_fds, extra_nfds, timeout_ms, ret, FALSE);
}