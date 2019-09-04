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
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  curl_mime ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_MIMEPOST ; 
 int /*<<< orphan*/  CURLOPT_NOPROGRESS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/ * curl_mime_addpart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_mime_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_mime_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 

int test(char *URL)
{
  CURL *curls = NULL;
  int res = 0;
  curl_mimepart *field = NULL;
  curl_mime *mime = NULL;

  global_init(CURL_GLOBAL_ALL);
  easy_init(curls);

  mime = curl_mime_init(curls);
  field = curl_mime_addpart(mime);
  curl_mime_name(field, "name");
  curl_mime_data(field, "short value", CURL_ZERO_TERMINATED);

  easy_setopt(curls, CURLOPT_URL, URL);
  easy_setopt(curls, CURLOPT_HEADER, 1L);
  easy_setopt(curls, CURLOPT_VERBOSE, 1L);
  easy_setopt(curls, CURLOPT_MIMEPOST, mime);
  easy_setopt(curls, CURLOPT_NOPROGRESS, 1L);

  res = curl_easy_perform(curls);
  if(res)
    goto test_cleanup;

  /* Alter form and resubmit. */
  curl_mime_data(field, "long value for length change", CURL_ZERO_TERMINATED);
  res = curl_easy_perform(curls);

test_cleanup:
  curl_mime_free(mime);
  curl_easy_cleanup(curls);
  curl_global_cleanup();
  return (int) res; /* return the final return code */
}