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
typedef  int /*<<< orphan*/  a ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 char* curl_easy_escape (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  static const unsigned char a[] = {
      0x9c, 0x26, 0x4b, 0x3d, 0x49, 0x4, 0xa1, 0x1,
      0xe0, 0xd8, 0x7c,  0x20, 0xb7, 0xef, 0x53, 0x29, 0xfa,
      0x1d, 0x57, 0xe1};

  CURL *easy;
  int asize;
  char *s;
  CURLcode res = CURLE_OK;
  (void)URL;

  global_init(CURL_GLOBAL_ALL);
  easy = curl_easy_init();
  if(!easy) {
    fprintf(stderr, "curl_easy_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  asize = (int)sizeof(a);

  s = curl_easy_escape(easy, (const char *)a, asize);

  if(s)
    printf("%s\n", s);

  if(s)
    curl_free(s);

  curl_easy_cleanup(easy);
  curl_global_cleanup();

  return 0;
}