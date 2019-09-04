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
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 

CURLcode Curl_posttransfer(struct Curl_easy *data)
{
#if defined(HAVE_SIGNAL) && defined(SIGPIPE) && !defined(HAVE_MSG_NOSIGNAL)
  /* restore the signal handler for SIGPIPE before we get back */
  if(!data->set.no_signal)
    signal(SIGPIPE, data->state.prev_signal);
#else
  (void)data; /* unused parameter */
#endif

  return CURLE_OK;
}