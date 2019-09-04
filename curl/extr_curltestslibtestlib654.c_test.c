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
struct curl_slist {int dummy; } ;
struct WriteThis {int freecount; scalar_t__ sizeleft; int /*<<< orphan*/  readptr; } ;
typedef  scalar_t__ curl_off_t ;
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  char curl_mime ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_MIMEPOST ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
 int TEST_ERR_FAILURE ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_duphandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curl_mime_addpart (char*) ; 
 int /*<<< orphan*/  curl_mime_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_mime_data_cb (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct WriteThis*) ; 
 int /*<<< orphan*/  curl_mime_encoder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_mime_filedata (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_mime_free (char*) ; 
 int /*<<< orphan*/  curl_mime_headers (int /*<<< orphan*/ *,struct curl_slist*,int /*<<< orphan*/ ) ; 
 char* curl_mime_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_mime_type (int /*<<< orphan*/ *,char*) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_callback ; 
 int /*<<< orphan*/  read_callback ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  CURL *easy = NULL;
  CURL *easy2 = NULL;
  curl_mime *mime = NULL;
  curl_mimepart *part;
  struct curl_slist *hdrs = NULL;
  CURLcode result;
  int res = TEST_ERR_FAILURE;
  struct WriteThis pooh;

  /*
   * Check proper copy/release of mime post data bound to a duplicated
   * easy handle.
   */

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  easy = curl_easy_init();

  /* First set the URL that is about to receive our POST. */
  test_setopt(easy, CURLOPT_URL, URL);

  /* get verbose debug output please */
  test_setopt(easy, CURLOPT_VERBOSE, 1L);

  /* include headers in the output */
  test_setopt(easy, CURLOPT_HEADER, 1L);

  /* Prepare the callback structure. */
  pooh.readptr = data;
  pooh.sizeleft = (curl_off_t) strlen(data);
  pooh.freecount = 0;

  /* Build the mime tree. */
  mime = curl_mime_init(easy);
  part = curl_mime_addpart(mime);
  curl_mime_data(part, "hello", CURL_ZERO_TERMINATED);
  curl_mime_name(part, "greeting");
  curl_mime_type(part, "application/X-Greeting");
  curl_mime_encoder(part, "base64");
  hdrs = curl_slist_append(hdrs, "X-Test-Number: 654");
  curl_mime_headers(part, hdrs, TRUE);
  part = curl_mime_addpart(mime);
  curl_mime_filedata(part, "log/file654.txt");
  part = curl_mime_addpart(mime);
  curl_mime_data_cb(part, (curl_off_t) -1, read_callback, NULL, free_callback,
                    &pooh);

  /* Bind mime data to its easy handle. */
  test_setopt(easy, CURLOPT_MIMEPOST, mime);

  /* Duplicate the handle. */
  easy2 = curl_easy_duphandle(easy);
  if(!easy2) {
    fprintf(stderr, "curl_easy_duphandle() failed\n");
    res = TEST_ERR_FAILURE;
    goto test_cleanup;
  }

  /* Now free the mime structure: it should unbind it from the first
     easy handle. */
  curl_mime_free(mime);
  mime = NULL;  /* Already cleaned up. */

  /* Perform on the first handle: should not send any data. */
  result = curl_easy_perform(easy);
  if(result) {
    fprintf(stderr, "curl_easy_perform(original) failed\n");
    res = (int) result;
    goto test_cleanup;
  }

  /* Perform on the second handle: if the bound mime structure has not been
     duplicated properly, it should cause a valgrind error. */
  result = curl_easy_perform(easy2);
  if(result) {
    fprintf(stderr, "curl_easy_perform(duplicated) failed\n");
    res = (int) result;
    goto test_cleanup;
  }

  /* Free the duplicated handle: it should call free_callback again.
     If the mime copy was bad or not automatically released, valgrind
     will signal it. */
  curl_easy_cleanup(easy2);
  easy2 = NULL;  /* Already cleaned up. */

  if(pooh.freecount != 2) {
    fprintf(stderr, "free_callback() called %d times instead of 2\n",
            pooh.freecount);
    res = TEST_ERR_FAILURE;
    goto test_cleanup;
  }

test_cleanup:
  curl_easy_cleanup(easy);
  curl_easy_cleanup(easy2);
  curl_mime_free(mime);
  curl_global_cleanup();
  return res;
}