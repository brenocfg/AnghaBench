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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  char* curl_off_t ;
typedef  char FILE ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_FTPPORT ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int TEST_ERR_FOPEN ; 
 int TEST_ERR_FSTAT ; 
 int TEST_ERR_USAGE ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (char*) ; 
 int /*<<< orphan*/  fileno (char*) ; 
 char* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fstat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* libtest_arg2 ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  res_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int test(char *URL)
{
  int res = 0;
  CURL *curl = NULL;
  FILE *hd_src = NULL;
  int hd;
  struct_stat file_info;
  CURLM *m = NULL;
  int running;

  start_test_timing();

  if(!libtest_arg2) {
#ifdef LIB529
    /* test 529 */
    fprintf(stderr, "Usage: lib529 [url] [uploadfile]\n");
#else
    /* test 525 */
    fprintf(stderr, "Usage: lib525 [url] [uploadfile]\n");
#endif
    return TEST_ERR_USAGE;
  }

  hd_src = fopen(libtest_arg2, "rb");
  if(NULL == hd_src) {
    fprintf(stderr, "fopen failed with error: %d (%s)\n",
            errno, strerror(errno));
    fprintf(stderr, "Error opening file: (%s)\n", libtest_arg2);
    return TEST_ERR_FOPEN;
  }

  /* get the file size of the local file */
  hd = fstat(fileno(hd_src), &file_info);
  if(hd == -1) {
    /* can't open file, bail out */
    fprintf(stderr, "fstat() failed with error: %d (%s)\n",
            errno, strerror(errno));
    fprintf(stderr, "ERROR: cannot open file (%s)\n", libtest_arg2);
    fclose(hd_src);
    return TEST_ERR_FSTAT;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    fclose(hd_src);
    return res;
  }

  easy_init(curl);

  /* enable uploading */
  easy_setopt(curl, CURLOPT_UPLOAD, 1L);

  /* specify target */
  easy_setopt(curl, CURLOPT_URL, URL);

  /* go verbose */
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* use active FTP */
  easy_setopt(curl, CURLOPT_FTPPORT, "-");

  /* now specify which file to upload */
  easy_setopt(curl, CURLOPT_READDATA, hd_src);

  /* NOTE: if you want this code to work on Windows with libcurl as a DLL, you
     MUST also provide a read callback with CURLOPT_READFUNCTION. Failing to
     do so will give you a crash since a DLL may not use the variable's memory
     when passed in to it from an app like this. */

  /* Set the size of the file to upload (optional).  If you give a *_LARGE
     option you MUST make sure that the type of the passed-in argument is a
     curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
     make sure that to pass in a type 'long' argument. */
  easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);

  multi_init(m);

  multi_add_handle(m, curl);

  for(;;) {
    struct timeval interval;
    fd_set rd, wr, exc;
    int maxfd = -99;

    interval.tv_sec = 1;
    interval.tv_usec = 0;

    multi_perform(m, &running);

    abort_on_test_timeout();

    if(!running)
      break; /* done */

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&exc);

    multi_fdset(m, &rd, &wr, &exc, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd + 1, &rd, &wr, &exc, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

#ifdef LIB529
  /* test 529 */
  /* proper cleanup sequence - type PA */
  curl_multi_remove_handle(m, curl);
  curl_multi_cleanup(m);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
#else
  /* test 525 */
  /* proper cleanup sequence - type PB */
  curl_multi_remove_handle(m, curl);
  curl_easy_cleanup(curl);
  curl_multi_cleanup(m);
  curl_global_cleanup();
#endif

  /* close the local file */
  fclose(hd_src);

  return res;
}