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
struct WildcardData {int /*<<< orphan*/  state; int /*<<< orphan*/ * customptr; int /*<<< orphan*/ * pattern; int /*<<< orphan*/ * path; int /*<<< orphan*/  filelist; int /*<<< orphan*/ * protdata; int /*<<< orphan*/  (* dtor ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURLWC_INIT ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUGASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void Curl_wildcard_dtor(struct WildcardData *wc)
{
  if(!wc)
    return;

  if(wc->dtor) {
    wc->dtor(wc->protdata);
    wc->dtor = ZERO_NULL;
    wc->protdata = NULL;
  }
  DEBUGASSERT(wc->protdata == NULL);

  Curl_llist_destroy(&wc->filelist, NULL);


  free(wc->path);
  wc->path = NULL;
  free(wc->pattern);
  wc->pattern = NULL;

  wc->customptr = NULL;
  wc->state = CURLWC_INIT;
}