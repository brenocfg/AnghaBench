#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ st_size; } ;
typedef  TYPE_1__ struct_stat ;
typedef  char curl_slist ;
typedef  char* curl_off_t ;
typedef  char FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_POSTFIELDS ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_RTSPHEADER ; 
 int /*<<< orphan*/  CURLOPT_RTSP_REQUEST ; 
 int /*<<< orphan*/  CURLOPT_RTSP_STREAM_URI ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 char* CURL_RTSPREQ_ANNOUNCE ; 
 char* CURL_RTSPREQ_DESCRIBE ; 
 char* CURL_RTSPREQ_OPTIONS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 char* curl_slist_append (char*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  fclose (char*) ; 
 char* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fstat (int,TYPE_1__*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* stdout ; 
 char* suburl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  int res;
  CURL *curl;
  int sdp;
  FILE *sdpf = NULL;
  struct_stat file_info;
  char *stream_uri = NULL;
  int request = 1;
  struct curl_slist *custom_headers = NULL;

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

  test_setopt(curl, CURLOPT_URL, URL);

  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  sdp = open("log/file568.txt", O_RDONLY);
  fstat(sdp, &file_info);
  close(sdp);

  sdpf = fopen("log/file568.txt", "rb");
  if(sdpf == NULL) {
    fprintf(stderr, "can't open log/file568.txt\n");
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_ANNOUNCE);

  test_setopt(curl, CURLOPT_READDATA, sdpf);
  test_setopt(curl, CURLOPT_UPLOAD, 1L);
  test_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t) file_info.st_size);

  /* Do the ANNOUNCE */
  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  test_setopt(curl, CURLOPT_UPLOAD, 0L);
  fclose(sdpf);
  sdpf = NULL;

  /* Make sure we can do a normal request now */
  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_DESCRIBE);
  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  /* Now do a POST style one */

  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  custom_headers = curl_slist_append(custom_headers,
                                     "Content-Type: posty goodness");
  if(!custom_headers) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSPHEADER, custom_headers);
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_ANNOUNCE);
  test_setopt(curl, CURLOPT_POSTFIELDS,
              "postyfield=postystuff&project=curl\n");

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  test_setopt(curl, CURLOPT_POSTFIELDS, NULL);
  test_setopt(curl, CURLOPT_RTSPHEADER, NULL);
  curl_slist_free_all(custom_headers);
  custom_headers = NULL;

  /* Make sure we can do a normal request now */
  stream_uri = suburl(URL, request++);
  if(!stream_uri) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_OPTIONS);
  res = curl_easy_perform(curl);

test_cleanup:

  if(sdpf)
    fclose(sdpf);

  free(stream_uri);

  if(custom_headers)
    curl_slist_free_all(custom_headers);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}