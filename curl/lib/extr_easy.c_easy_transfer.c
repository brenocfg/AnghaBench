#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Curl_multi {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  result; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  TYPE_2__ CURLMsg ;
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLM_OK ; 
 scalar_t__ CURLM_OUT_OF_MEMORY ; 
 int FALSE ; 
 int TRUE ; 
 TYPE_2__* curl_multi_info_read (struct Curl_multi*,int*) ; 
 scalar_t__ curl_multi_perform (struct Curl_multi*,int*) ; 
 scalar_t__ curl_multi_poll (struct Curl_multi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode easy_transfer(struct Curl_multi *multi)
{
  bool done = FALSE;
  CURLMcode mcode = CURLM_OK;
  CURLcode result = CURLE_OK;

  while(!done && !mcode) {
    int still_running = 0;

    mcode = curl_multi_poll(multi, NULL, 0, 1000, NULL);

    if(!mcode)
      mcode = curl_multi_perform(multi, &still_running);

    /* only read 'still_running' if curl_multi_perform() return OK */
    if(!mcode && !still_running) {
      int rc;
      CURLMsg *msg = curl_multi_info_read(multi, &rc);
      if(msg) {
        result = msg->data.result;
        done = TRUE;
      }
    }
  }

  /* Make sure to return some kind of error if there was a multi problem */
  if(mcode) {
    result = (mcode == CURLM_OUT_OF_MEMORY) ? CURLE_OUT_OF_MEMORY :
              /* The other multi errors should never happen, so return
                 something suitably generic */
              CURLE_BAD_FUNCTION_ARGUMENT;
  }

  return result;
}