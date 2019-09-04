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
struct curl_httppost {int dummy; } ;
struct WriteThis {void* sizeleft; void* readptr; } ;
typedef  int /*<<< orphan*/  curl_off_t ;
typedef  int CURLcode ;
typedef  scalar_t__ CURLFORMcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLFORM_BUFFER ; 
 int /*<<< orphan*/  CURLFORM_BUFFERLENGTH ; 
 int /*<<< orphan*/  CURLFORM_BUFFERPTR ; 
 int /*<<< orphan*/  CURLFORM_CONTENTLEN ; 
 int /*<<< orphan*/  CURLFORM_CONTENTSLENGTH ; 
 int /*<<< orphan*/  CURLFORM_CONTENTTYPE ; 
 int /*<<< orphan*/  CURLFORM_COPYCONTENTS ; 
 int /*<<< orphan*/  CURLFORM_COPYNAME ; 
 int /*<<< orphan*/  CURLFORM_END ; 
 int /*<<< orphan*/  CURLFORM_FILENAME ; 
 int /*<<< orphan*/  CURLFORM_STREAM ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_HTTPPOST ; 
 int /*<<< orphan*/  CURLOPT_POST ; 
 int /*<<< orphan*/  CURLOPT_POSTFIELDSIZE ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_formadd (struct curl_httppost**,struct curl_httppost**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_formfree (struct curl_httppost*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 void* data ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 long read_callback ; 
 int /*<<< orphan*/  stderr ; 
 void* strlen (void*) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int once(char *URL, bool oldstyle)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  CURLFORMcode formrc;

  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct WriteThis pooh;
  struct WriteThis pooh2;

  pooh.readptr = data;
  pooh.sizeleft = strlen(data);

  /* Fill in the file upload field */
  if(oldstyle) {
    formrc = curl_formadd(&formpost,
                          &lastptr,
                          CURLFORM_COPYNAME, "sendfile",
                          CURLFORM_STREAM, &pooh,
                          CURLFORM_CONTENTSLENGTH, (long)pooh.sizeleft,
                          CURLFORM_FILENAME, "postit2.c",
                          CURLFORM_END);
  }
  else {
    /* new style */
    formrc = curl_formadd(&formpost,
                          &lastptr,
                          CURLFORM_COPYNAME, "sendfile alternative",
                          CURLFORM_STREAM, &pooh,
                          CURLFORM_CONTENTLEN, (curl_off_t)pooh.sizeleft,
                          CURLFORM_FILENAME, "file name 2",
                          CURLFORM_END);
  }

  if(formrc)
    printf("curl_formadd(1) = %d\n", (int)formrc);

  /* Now add the same data with another name and make it not look like
     a file upload but still using the callback */

  pooh2.readptr = data;
  pooh2.sizeleft = strlen(data);

  /* Fill in the file upload field */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "callbackdata",
                        CURLFORM_STREAM, &pooh2,
                        CURLFORM_CONTENTSLENGTH, (long)pooh2.sizeleft,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(2) = %d\n", (int)formrc);

  /* Fill in the filename field */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "filename",
#ifdef CURL_DOES_CONVERSIONS
                        /* ASCII representation with escape
                           sequences for non-ASCII platforms */
                        CURLFORM_COPYCONTENTS,
                           "\x70\x6f\x73\x74\x69\x74\x32\x2e\x63",
#else
                        CURLFORM_COPYCONTENTS, "postit2.c",
#endif
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(3) = %d\n", (int)formrc);

  /* Fill in a submit field too */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "submit",
#ifdef CURL_DOES_CONVERSIONS
                        /* ASCII representation with escape
                           sequences for non-ASCII platforms */
                        CURLFORM_COPYCONTENTS, "\x73\x65\x6e\x64",
#else
                        CURLFORM_COPYCONTENTS, "send",
#endif
                        CURLFORM_CONTENTTYPE, "text/plain",
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(4) = %d\n", (int)formrc);

  formrc = curl_formadd(&formpost, &lastptr,
                        CURLFORM_COPYNAME, "somename",
                        CURLFORM_BUFFER, "somefile.txt",
                        CURLFORM_BUFFERPTR, "blah blah",
                        CURLFORM_BUFFERLENGTH, (long)9,
                        CURLFORM_END);

  if(formrc)
    printf("curl_formadd(5) = %d\n", (int)formrc);

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_formfree(formpost);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

  /* Now specify we want to POST data */
  test_setopt(curl, CURLOPT_POST, 1L);

  /* Set the expected POST size */
  test_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)pooh.sizeleft);

  /* we want to use our own read function */
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);

  /* send a multi-part formpost */
  test_setopt(curl, CURLOPT_HTTPPOST, formpost);

  /* get verbose debug output please */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* include headers in the output */
  test_setopt(curl, CURLOPT_HEADER, 1L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);

  /* now cleanup the formpost chain */
  curl_formfree(formpost);

  return res;
}