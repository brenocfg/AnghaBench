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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_RTSP_SESSION_ID ; 
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_RTSP_REQUEST ; 
 int /*<<< orphan*/  CURLOPT_RTSP_SESSION_ID ; 
 int /*<<< orphan*/  CURLOPT_RTSP_STREAM_URI ; 
 int /*<<< orphan*/  CURLOPT_RTSP_TRANSPORT ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 char* CURL_RTSPREQ_SETUP ; 
 char* CURL_RTSPREQ_TEARDOWN ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libtest_arg2 ; 
 int /*<<< orphan*/  stderr ; 
 char* stdout ; 
 char* suburl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  int res;
  CURL *curl;
  char *stream_uri = NULL;
  char *rtsp_session_id;
  int request = 1;
  int i;

  FILE *idfile = fopen(libtest_arg2, "wb");
  if(idfile == NULL) {
    fprintf(stderr, "couldn't open the Session ID File\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    fclose(idfile);
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    fclose(idfile);
    return TEST_ERR_MAJOR_BAD;
  }

  test_setopt(curl, CURLOPT_HEADERDATA, stdout);
  test_setopt(curl, CURLOPT_WRITEDATA, stdout);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  test_setopt(curl, CURLOPT_URL, URL);

  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_SETUP);
  res = curl_easy_perform(curl);
  if(res != (int)CURLE_BAD_FUNCTION_ARGUMENT) {
    fprintf(stderr, "This should have failed. "
            "Cannot setup without a Transport: header");
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  /* Go through the various Session IDs */
  for(i = 0; i < 3; i++) {
    stream_uri = suburl(URL, request++);
    if(!stream_uri) {
      res = TEST_ERR_MAJOR_BAD;
      goto test_cleanup;
    }
    test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
    free(stream_uri);
    stream_uri = NULL;

    test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_SETUP);
    test_setopt(curl, CURLOPT_RTSP_TRANSPORT,
                "Fake/NotReal/JustATest;foo=baz");
    res = curl_easy_perform(curl);
    if(res)
      goto test_cleanup;

    curl_easy_getinfo(curl, CURLINFO_RTSP_SESSION_ID, &rtsp_session_id);
    fprintf(idfile, "Got Session ID: [%s]\n", rtsp_session_id);
    rtsp_session_id = NULL;

    stream_uri = suburl(URL, request++);
    if(!stream_uri) {
      res = TEST_ERR_MAJOR_BAD;
      goto test_cleanup;
    }
    test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
    free(stream_uri);
    stream_uri = NULL;

    test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_TEARDOWN);
    res = curl_easy_perform(curl);

    /* Clear for the next go-round */
    test_setopt(curl, CURLOPT_RTSP_SESSION_ID, NULL);
  }

test_cleanup:

  if(idfile)
    fclose(idfile);

  free(stream_uri);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}