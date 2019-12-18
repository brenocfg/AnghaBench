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
struct timeval {int dummy; } ;
struct per_transfer {int dummy; } ;
struct GlobalConfig {int dummy; } ;
struct TYPE_4__ {scalar_t__ result; } ;
struct TYPE_5__ {TYPE_1__ data; int /*<<< orphan*/ * easy_handle; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURLSH ;
typedef  TYPE_2__ CURLMsg ;
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLINFO_PRIVATE ; 
 scalar_t__ CURLM_OK ; 
 scalar_t__ CURLM_OUT_OF_MEMORY ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ add_parallel_transfers (struct GlobalConfig*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  all_added ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 TYPE_2__* curl_multi_info_read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 scalar_t__ curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ curl_multi_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_per_transfer (struct per_transfer*) ; 
 scalar_t__ post_per_transfer (struct GlobalConfig*,struct per_transfer*,scalar_t__,int*) ; 
 int /*<<< orphan*/  progress_finalize (struct per_transfer*) ; 
 int /*<<< orphan*/  progress_meter (struct GlobalConfig*,struct timeval*,int) ; 
 struct timeval tvnow () ; 

__attribute__((used)) static CURLcode parallel_transfers(struct GlobalConfig *global,
                                   CURLSH *share)
{
  CURLM *multi;
  CURLMcode mcode = CURLM_OK;
  CURLcode result = CURLE_OK;
  int still_running = 1;
  struct timeval start = tvnow();
  bool more_transfers;
  bool added_transfers;

  multi = curl_multi_init();
  if(!multi)
    return CURLE_OUT_OF_MEMORY;

  result = add_parallel_transfers(global, multi, share,
                                  &more_transfers, &added_transfers);
  if(result)
    return result;

  while(!mcode && (still_running || more_transfers)) {
    mcode = curl_multi_poll(multi, NULL, 0, 1000, NULL);
    if(!mcode)
      mcode = curl_multi_perform(multi, &still_running);

    progress_meter(global, &start, FALSE);

    if(!mcode) {
      int rc;
      CURLMsg *msg;
      bool removed = FALSE;
      do {
        msg = curl_multi_info_read(multi, &rc);
        if(msg) {
          bool retry;
          struct per_transfer *ended;
          CURL *easy = msg->easy_handle;
          result = msg->data.result;
          curl_easy_getinfo(easy, CURLINFO_PRIVATE, (void *)&ended);
          curl_multi_remove_handle(multi, easy);

          result = post_per_transfer(global, ended, result, &retry);
          if(retry)
            continue;
          progress_finalize(ended); /* before it goes away */
          all_added--; /* one fewer added */
          removed = TRUE;
          (void)del_per_transfer(ended);
        }
      } while(msg);
      if(removed) {
        /* one or more transfers completed, add more! */
        (void)add_parallel_transfers(global, multi, share,
                                     &more_transfers,
                                     &added_transfers);
        if(added_transfers)
          /* we added new ones, make sure the loop doesn't exit yet */
          still_running = 1;
      }
    }
  }

  (void)progress_meter(global, &start, TRUE);

  /* Make sure to return some kind of error if there was a multi problem */
  if(mcode) {
    result = (mcode == CURLM_OUT_OF_MEMORY) ? CURLE_OUT_OF_MEMORY :
      /* The other multi errors should never happen, so return
         something suitably generic */
      CURLE_BAD_FUNCTION_ARGUMENT;
  }

  curl_multi_cleanup(multi);

  return result;
}