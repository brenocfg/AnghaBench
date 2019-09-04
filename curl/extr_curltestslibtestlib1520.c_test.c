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
struct upload_status {int /*<<< orphan*/  member_0; } ;
struct curl_slist {int dummy; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_MAIL_FROM ; 
 int /*<<< orphan*/  CURLOPT_MAIL_RCPT ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 long FROM ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  TO ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 long read_callback ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  CURLcode res;
  CURL *curl;
  struct curl_slist *rcpt_list = NULL;
  struct upload_status upload_ctx = {0};

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  rcpt_list = curl_slist_append(rcpt_list, TO);
  /* more addresses can be added here
     rcpt_list = curl_slist_append(rcpt_list, "<others@example.com>");
  */

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_UPLOAD, 1L);
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);
  test_setopt(curl, CURLOPT_READDATA, &upload_ctx);
  test_setopt(curl, CURLOPT_MAIL_FROM, FROM);
  test_setopt(curl, CURLOPT_MAIL_RCPT, rcpt_list);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  res = curl_easy_perform(curl);

test_cleanup:

  curl_slist_free_all(rcpt_list);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}