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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 scalar_t__ gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 

CURLcode Curl_gmtime(time_t intime, struct tm *store)
{
  const struct tm *tm;
#ifdef HAVE_GMTIME_R
  /* thread-safe version */
  tm = (struct tm *)gmtime_r(&intime, store);
#else
  tm = gmtime(&intime);
  if(tm)
    *store = *tm; /* copy the pointed struct to the local copy */
#endif

  if(!tm)
    return CURLE_BAD_FUNCTION_ARGUMENT;
  return CURLE_OK;
}