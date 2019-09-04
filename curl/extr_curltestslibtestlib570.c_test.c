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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_RTSP_CSEQ_ERROR ; 
 int CURLE_RTSP_SESSION_ERROR ; 
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_RTSP_CLIENT_CSEQ ; 
 int /*<<< orphan*/  CURLOPT_RTSP_REQUEST ; 
 int /*<<< orphan*/  CURLOPT_RTSP_STREAM_URI ; 
 int /*<<< orphan*/  CURLOPT_RTSP_TRANSPORT ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 char* CURL_RTSPREQ_OPTIONS ; 
 char* CURL_RTSPREQ_PLAY ; 
 char* CURL_RTSPREQ_SETUP ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* stdout ; 
 char* suburl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  int res;
  CURL *curl;
  int request = 1;
  char *stream_uri = NULL;

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

  test_setopt(curl, CURLOPT_HEADERDATA, stdout);
  test_setopt(curl, CURLOPT_WRITEDATA, stdout);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  test_setopt(curl, CURLOPT_URL, URL);

  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_OPTIONS);

  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  res = curl_easy_perform(curl);
  if(res != (int)CURLE_RTSP_CSEQ_ERROR) {
    fprintf(stderr, "Failed to detect CSeq mismatch");
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  test_setopt(curl, CURLOPT_RTSP_CLIENT_CSEQ, 999L);
  test_setopt(curl, CURLOPT_RTSP_TRANSPORT,
                    "RAW/RAW/UDP;unicast;client_port=3056-3057");
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_SETUP);

  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_PLAY);

  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  res = curl_easy_perform(curl);
  if(res != CURLE_RTSP_SESSION_ERROR) {
    fprintf(stderr, "Failed to detect a Session ID mismatch");
  }

test_cleanup:
  free(stream_uri);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}