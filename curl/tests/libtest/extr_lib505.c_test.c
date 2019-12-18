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
typedef  int CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_POSTQUOTE ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 int TEST_ERR_USAGE ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 char* curl_slist_append (char*,char const*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (char*) ; 
 int /*<<< orphan*/  fileno (char*) ; 
 char* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fstat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* libtest_arg2 ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  FILE *hd_src;
  int hd;
  struct_stat file_info;
  struct curl_slist *hl;

  struct curl_slist *headerlist = NULL;
  const char *buf_1 = "RNFR 505";
  const char *buf_2 = "RNTO 505-forreal";

  if(!libtest_arg2) {
    fprintf(stderr, "Usage: <url> <file-to-upload>\n");
    return TEST_ERR_USAGE;
  }

  hd_src = fopen(libtest_arg2, "rb");
  if(NULL == hd_src) {
    fprintf(stderr, "fopen failed with error: %d %s\n",
            errno, strerror(errno));
    fprintf(stderr, "Error opening file: %s\n", libtest_arg2);
    return TEST_ERR_MAJOR_BAD; /* if this happens things are major weird */
  }

  /* get the file size of the local file */
  hd = fstat(fileno(hd_src), &file_info);
  if(hd == -1) {
    /* can't open file, bail out */
    fprintf(stderr, "fstat() failed with error: %d %s\n",
            errno, strerror(errno));
    fprintf(stderr, "ERROR: cannot open file %s\n", libtest_arg2);
    fclose(hd_src);
    return TEST_ERR_MAJOR_BAD;
  }

  if(! file_info.st_size) {
    fprintf(stderr, "ERROR: file %s has zero size!\n", libtest_arg2);
    fclose(hd_src);
    return TEST_ERR_MAJOR_BAD;
  }

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    fclose(hd_src);
    return TEST_ERR_MAJOR_BAD;
  }

  /* get a curl handle */
  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    fclose(hd_src);
    return TEST_ERR_MAJOR_BAD;
  }

  /* build a list of commands to pass to libcurl */

  hl = curl_slist_append(headerlist, buf_1);
  if(!hl) {
    fprintf(stderr, "curl_slist_append() failed\n");
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    fclose(hd_src);
    return TEST_ERR_MAJOR_BAD;
  }
  headerlist = curl_slist_append(hl, buf_2);
  if(!headerlist) {
    fprintf(stderr, "curl_slist_append() failed\n");
    curl_slist_free_all(hl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    fclose(hd_src);
    return TEST_ERR_MAJOR_BAD;
  }
  headerlist = hl;

  /* enable uploading */
  test_setopt(curl, CURLOPT_UPLOAD, 1L);

  /* enable verbose */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* specify target */
  test_setopt(curl, CURLOPT_URL, URL);

  /* pass in that last of FTP commands to run after the transfer */
  test_setopt(curl, CURLOPT_POSTQUOTE, headerlist);

  /* now specify which file to upload */
  test_setopt(curl, CURLOPT_READDATA, hd_src);

  /* and give the size of the upload (optional) */
  test_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                   (curl_off_t)file_info.st_size);

  /* Now run off and do what you've been told! */
  res = curl_easy_perform(curl);

test_cleanup:

  /* clean up the FTP commands list */
  curl_slist_free_all(headerlist);

  /* close the local file */
  fclose(hd_src);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}