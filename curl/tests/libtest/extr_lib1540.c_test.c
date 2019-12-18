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
struct transfer_status {int /*<<< orphan*/ * easy; } ;
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_HEADERFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_NOPROGRESS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_XFERINFODATA ; 
 int /*<<< orphan*/  CURLOPT_XFERINFOFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 long header_callback ; 
 int /*<<< orphan*/  memset (struct transfer_status*,int /*<<< orphan*/ ,int) ; 
 long please_continue ; 
 int /*<<< orphan*/  start_test_timing () ; 
 long write_callback ; 

int test(char *URL)
{
  CURL *curls = NULL;
  int i = 0;
  int res = 0;
  struct transfer_status st;

  start_test_timing();

  memset(&st, 0, sizeof(st));

  global_init(CURL_GLOBAL_ALL);

  easy_init(curls);
  st.easy = curls; /* to allow callbacks access */

  easy_setopt(curls, CURLOPT_URL, URL);
  easy_setopt(curls, CURLOPT_WRITEFUNCTION, write_callback);
  easy_setopt(curls, CURLOPT_WRITEDATA, &st);
  easy_setopt(curls, CURLOPT_HEADERFUNCTION, header_callback);
  easy_setopt(curls, CURLOPT_HEADERDATA, &st);

  easy_setopt(curls, CURLOPT_XFERINFOFUNCTION, please_continue);
  easy_setopt(curls, CURLOPT_XFERINFODATA, &st);
  easy_setopt(curls, CURLOPT_NOPROGRESS, 0L);

  res = curl_easy_perform(curls);

test_cleanup:

  curl_easy_cleanup(curls);
  curl_global_cleanup();

  if(res)
    i = res;

  return i; /* return the final return code */
}