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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_AGAIN ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_CONNECT_ONLY ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ TEST_ERR_FAILURE ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_easy_recv (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 scalar_t__ curl_easy_send (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 

int test(char *URL)
{
  CURLcode res;
  CURL *curl;

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

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  res = curl_easy_perform(curl);

  if(!res) {
    /* we are connected, now get a HTTP document the raw way */
    const char *request =
#ifdef CURL_DOES_CONVERSIONS
      /* ASCII representation with escape sequences for non-ASCII platforms */
      "\x47\x45\x54\x20\x2f\x35\x35\x36\x20\x48\x54\x54\x50\x2f\x31\x2e"
      "\x32\x0d\x0a\x48\x6f\x73\x74\x3a\x20\x6e\x69\x6e\x6a\x61\x0d\x0a"
      "\x0d\x0a";
#else
      "GET /556 HTTP/1.2\r\n"
      "Host: ninja\r\n\r\n";
#endif
    size_t iolen = 0;

    res = curl_easy_send(curl, request, strlen(request), &iolen);

    if(!res) {
      /* we assume that sending always work */

      do {
        char buf[1024];
        /* busy-read like crazy */
        res = curl_easy_recv(curl, buf, sizeof(buf), &iolen);

#ifdef TPF
        sleep(1); /* avoid ctl-10 dump */
#endif

        if(iolen) {
          /* send received stuff to stdout */
          if(!write(STDOUT_FILENO, buf, iolen))
            break;
        }

      } while((res == CURLE_OK && iolen != 0) || (res == CURLE_AGAIN));
    }

    if(iolen != 0)
      res = TEST_ERR_FAILURE;
  }

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}