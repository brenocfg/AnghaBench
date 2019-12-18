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
struct WriteThis {void* sizeleft; void* readptr; } ;
typedef  void* curl_off_t ;
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  curl_mime ;
typedef  int CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_MIMEPOST ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 char* curl_easy_strerror (int) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/ * curl_mime_addpart (int /*<<< orphan*/ *) ; 
 int curl_mime_data (int /*<<< orphan*/ *,char*,...) ; 
 int curl_mime_data_cb (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct WriteThis*) ; 
 int curl_mime_filename (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_mime_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_mime_init (int /*<<< orphan*/ *) ; 
 int curl_mime_name (int /*<<< orphan*/ *,char*) ; 
 void* data ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read_callback ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int once(char *URL, bool oldstyle)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  curl_mime *mime = NULL;
  curl_mimepart *part = NULL;
  struct WriteThis pooh;
  struct WriteThis pooh2;
  curl_off_t datasize = -1;

  pooh.readptr = data;
#ifndef LIB645
  datasize = (curl_off_t)strlen(data);
#endif
  pooh.sizeleft = datasize;

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  mime = curl_mime_init(curl);
  if(!mime) {
    fprintf(stderr, "curl_mime_init() failed\n");
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  part = curl_mime_addpart(mime);
  if(!part) {
    fprintf(stderr, "curl_mime_addpart(1) failed\n");
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* Fill in the file upload part */
  if(oldstyle) {
    res = curl_mime_name(part, "sendfile");
    if(!res)
      res = curl_mime_data_cb(part, datasize, read_callback,
                              NULL, NULL, &pooh);
    if(!res)
      res = curl_mime_filename(part, "postit2.c");
  }
  else {
    /* new style */
    res = curl_mime_name(part, "sendfile alternative");
    if(!res)
      res = curl_mime_data_cb(part, datasize, read_callback,
                              NULL, NULL, &pooh);
    if(!res)
      res = curl_mime_filename(part, "file name 2");
  }

  if(res)
    printf("curl_mime_xxx(1) = %s\n", curl_easy_strerror(res));

  /* Now add the same data with another name and make it not look like
     a file upload but still using the callback */

  pooh2.readptr = data;
#ifndef LIB645
  datasize = (curl_off_t)strlen(data);
#endif
  pooh2.sizeleft = datasize;

  part = curl_mime_addpart(mime);
  if(!part) {
    fprintf(stderr, "curl_mime_addpart(2) failed\n");
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }
  /* Fill in the file upload part */
  res = curl_mime_name(part, "callbackdata");
  if(!res)
    res = curl_mime_data_cb(part, datasize, read_callback,
                            NULL, NULL, &pooh2);

  if(res)
    printf("curl_mime_xxx(2) = %s\n", curl_easy_strerror(res));

  part = curl_mime_addpart(mime);
  if(!part) {
    fprintf(stderr, "curl_mime_addpart(3) failed\n");
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* Fill in the filename field */
  res = curl_mime_name(part, "filename");
  if(!res)
    res = curl_mime_data(part,
#ifdef CURL_DOES_CONVERSIONS
                         /* ASCII representation with escape
                            sequences for non-ASCII platforms */
                         "\x70\x6f\x73\x74\x69\x74\x32\x2e\x63",
#else
                          "postit2.c",
#endif
                          CURL_ZERO_TERMINATED);

  if(res)
    printf("curl_mime_xxx(3) = %s\n", curl_easy_strerror(res));

  /* Fill in a submit field too */
  part = curl_mime_addpart(mime);
  if(!part) {
    fprintf(stderr, "curl_mime_addpart(4) failed\n");
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }
  res = curl_mime_name(part, "submit");
  if(!res)
    res = curl_mime_data(part,
#ifdef CURL_DOES_CONVERSIONS
                         /* ASCII representation with escape
                            sequences for non-ASCII platforms */
                         "\x73\x65\x6e\x64",
#else
                          "send",
#endif
                          CURL_ZERO_TERMINATED);

  if(res)
    printf("curl_mime_xxx(4) = %s\n", curl_easy_strerror(res));

  part = curl_mime_addpart(mime);
  if(!part) {
    fprintf(stderr, "curl_mime_addpart(5) failed\n");
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }
  res = curl_mime_name(part, "somename");
  if(!res)
    res = curl_mime_filename(part, "somefile.txt");
  if(!res)
    res = curl_mime_data(part, "blah blah", 9);

  if(res)
    printf("curl_mime_xxx(5) = %s\n", curl_easy_strerror(res));

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

  /* send a multi-part mimepost */
  test_setopt(curl, CURLOPT_MIMEPOST, mime);

  /* get verbose debug output please */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* include headers in the output */
  test_setopt(curl, CURLOPT_HEADER, 1L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);

  /* now cleanup the mimepost structure */
  curl_mime_free(mime);

  return res;
}