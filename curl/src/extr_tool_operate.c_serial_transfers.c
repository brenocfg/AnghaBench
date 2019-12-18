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
struct per_transfer {int /*<<< orphan*/  mlfile; int /*<<< orphan*/  curl; } ;
struct GlobalConfig {int /*<<< orphan*/  current; scalar_t__ fail_early; scalar_t__ test_event_based; scalar_t__ libcurl; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURLSH ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ create_transfer (struct GlobalConfig*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ ) ; 
 scalar_t__ curl_easy_perform_ev (int /*<<< orphan*/ ) ; 
 struct per_transfer* del_per_transfer (struct per_transfer*) ; 
 int /*<<< orphan*/  delete_metalinkfile (int /*<<< orphan*/ ) ; 
 scalar_t__ easysrc_perform () ; 
 scalar_t__ is_fatal_error (scalar_t__) ; 
 scalar_t__ post_per_transfer (struct GlobalConfig*,struct per_transfer*,scalar_t__,int*) ; 
 scalar_t__ pre_transfer (struct GlobalConfig*,struct per_transfer*) ; 
 int /*<<< orphan*/  single_transfer_cleanup (int /*<<< orphan*/ ) ; 
 struct per_transfer* transfers ; 

__attribute__((used)) static CURLcode serial_transfers(struct GlobalConfig *global,
                                 CURLSH *share)
{
  CURLcode returncode = CURLE_OK;
  CURLcode result = CURLE_OK;
  struct per_transfer *per;
  bool added = FALSE;

  result = create_transfer(global, share, &added);
  if(result || !added)
    return result;
  for(per = transfers; per;) {
    bool retry;
    bool bailout = FALSE;
    result = pre_transfer(global, per);
    if(result)
      break;

#ifndef CURL_DISABLE_LIBCURL_OPTION
    if(global->libcurl) {
      result = easysrc_perform();
      if(result)
        break;
    }
#endif
#ifdef CURLDEBUG
    if(global->test_event_based)
      result = curl_easy_perform_ev(per->curl);
    else
#endif
      result = curl_easy_perform(per->curl);

    /* store the result of the actual transfer */
    returncode = result;

    result = post_per_transfer(global, per, result, &retry);
    if(retry)
      continue;

    /* Bail out upon critical errors or --fail-early */
    if(result || is_fatal_error(returncode) ||
       (returncode && global->fail_early))
      bailout = TRUE;
    else {
      /* setup the next one just before we delete this */
      result = create_transfer(global, share, &added);
      if(result)
        bailout = TRUE;
    }

    /* Release metalink related resources here */
    delete_metalinkfile(per->mlfile);

    per = del_per_transfer(per);

    if(bailout)
      break;
  }
  if(returncode)
    /* returncode errors have priority */
    result = returncode;

  if(result)
    single_transfer_cleanup(global->current);

  return result;
}