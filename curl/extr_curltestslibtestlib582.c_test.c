#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ st_size; } ;
typedef  TYPE_2__ struct_stat ;
struct TYPE_8__ {int /*<<< orphan*/  sockets; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct timeval {int member_0; int tv_sec; int tv_usec; TYPE_3__ write; TYPE_3__ read; TYPE_1__ member_1; } ;
struct ReadWriteSockets {int member_0; int tv_sec; int tv_usec; TYPE_3__ write; TYPE_3__ read; TYPE_1__ member_1; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ curl_socket_t ;
typedef  long curl_off_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_SOCKETDATA ; 
 int /*<<< orphan*/  CURLMOPT_SOCKETFUNCTION ; 
 int /*<<< orphan*/  CURLMOPT_TIMERDATA ; 
 int /*<<< orphan*/  CURLMOPT_TIMERFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_SSH_PRIVATE_KEYFILE ; 
 int /*<<< orphan*/  CURLOPT_SSH_PUBLIC_KEYFILE ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYHOST ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERPWD ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_CSELECT_IN ; 
 int /*<<< orphan*/  CURL_CSELECT_OUT ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  CURL_SOCKET_TIMEOUT ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int TEST_ERR_FOPEN ; 
 int TEST_ERR_FSTAT ; 
 int TEST_ERR_MAJOR_BAD ; 
 int TEST_ERR_USAGE ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  checkFdSet (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  checkForCompletion (int /*<<< orphan*/ *,int*) ; 
 struct timeval* curlSocketCallback ; 
 struct timeval* curlTimerCallback ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int fstat (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int getMicroSecondTimeout (struct timeval*) ; 
 char* libtest_arg2 ; 
 long libtest_arg3 ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  notifyCurl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  res_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  updateFdSet (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 

int test(char *URL)
{
  int res = 0;
  CURL *curl = NULL;
  FILE *hd_src = NULL;
  int hd;
  struct_stat file_info;
  CURLM *m = NULL;
  struct ReadWriteSockets sockets = {{NULL, 0, 0}, {NULL, 0, 0}};
  struct timeval timeout = {-1, 0};
  int success = 0;

  start_test_timing();

  if(!libtest_arg3) {
    fprintf(stderr, "Usage: lib582 [url] [filename] [username]\n");
    return TEST_ERR_USAGE;
  }

  hd_src = fopen(libtest_arg2, "rb");
  if(NULL == hd_src) {
    fprintf(stderr, "fopen() failed with error: %d (%s)\n",
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
  fprintf(stderr, "Set to upload %d bytes\n", (int)file_info.st_size);

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

  /* now specify which file to upload */
  easy_setopt(curl, CURLOPT_READDATA, hd_src);

  easy_setopt(curl, CURLOPT_USERPWD, libtest_arg3);
  easy_setopt(curl, CURLOPT_SSH_PUBLIC_KEYFILE, "curl_client_key.pub");
  easy_setopt(curl, CURLOPT_SSH_PRIVATE_KEYFILE, "curl_client_key");
  easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

  easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);

  multi_init(m);

  multi_setopt(m, CURLMOPT_SOCKETFUNCTION, curlSocketCallback);
  multi_setopt(m, CURLMOPT_SOCKETDATA, &sockets);

  multi_setopt(m, CURLMOPT_TIMERFUNCTION, curlTimerCallback);
  multi_setopt(m, CURLMOPT_TIMERDATA, &timeout);

  multi_add_handle(m, curl);

  while(!checkForCompletion(m, &success)) {
    fd_set readSet, writeSet;
    curl_socket_t maxFd = 0;
    struct timeval tv = {10, 0};

    FD_ZERO(&readSet);
    FD_ZERO(&writeSet);
    updateFdSet(&sockets.read, &readSet, &maxFd);
    updateFdSet(&sockets.write, &writeSet, &maxFd);

    if(timeout.tv_sec != -1) {
      int usTimeout = getMicroSecondTimeout(&timeout);
      tv.tv_sec = usTimeout / 1000000;
      tv.tv_usec = usTimeout % 1000000;
    }
    else if(maxFd <= 0) {
      tv.tv_sec = 0;
      tv.tv_usec = 100000;
    }

    select_test((int)maxFd, &readSet, &writeSet, NULL, &tv);

    /* Check the sockets for reading / writing */
    checkFdSet(m, &sockets.read, &readSet, CURL_CSELECT_IN, "read");
    checkFdSet(m, &sockets.write, &writeSet, CURL_CSELECT_OUT, "write");

    if(timeout.tv_sec != -1 && getMicroSecondTimeout(&timeout) == 0) {
      /* Curl's timer has elapsed. */
      notifyCurl(m, CURL_SOCKET_TIMEOUT, 0, "timeout");
    }

    abort_on_test_timeout();
  }

  if(!success) {
    fprintf(stderr, "Error uploading file.\n");
    res = TEST_ERR_MAJOR_BAD;
  }

test_cleanup:

  /* proper cleanup sequence - type PB */

  curl_multi_remove_handle(m, curl);
  curl_easy_cleanup(curl);
  curl_multi_cleanup(m);
  curl_global_cleanup();

  /* close the local file */
  fclose(hd_src);

  /* free local memory */
  free(sockets.read.sockets);
  free(sockets.write.sockets);

  return res;
}