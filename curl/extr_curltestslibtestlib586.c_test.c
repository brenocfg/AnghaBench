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
struct userdata {char* text; scalar_t__ counter; } ;
struct Tdata {char* url; char* share; } ;
typedef  scalar_t__ CURLSHcode ;
typedef  char CURLSH ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_SHARE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 scalar_t__ CURLSHE_OK ; 
 int /*<<< orphan*/  CURLSHOPT_LOCKFUNC ; 
 int /*<<< orphan*/  CURLSHOPT_SHARE ; 
 int /*<<< orphan*/  CURLSHOPT_UNLOCKFUNC ; 
 int /*<<< orphan*/  CURLSHOPT_USERDATA ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 struct userdata* CURL_LOCK_DATA_SSL_SESSION ; 
 int TEST_ERR_MAJOR_BAD ; 
 int THREADS ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 scalar_t__ curl_share_cleanup (char*) ; 
 char* curl_share_init () ; 
 scalar_t__ curl_share_setopt (char*,int /*<<< orphan*/ ,struct userdata*) ; 
 int /*<<< orphan*/  fire (struct Tdata*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct userdata* my_lock ; 
 struct userdata* my_unlock ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int test(char *URL)
{
  int res;
  CURLSHcode scode = CURLSHE_OK;
  char *url;
  struct Tdata tdata;
  CURL *curl;
  CURLSH *share;
  int i;
  struct userdata user;

  user.text = "Pigs in space";
  user.counter = 0;

  printf("GLOBAL_INIT\n");
  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* prepare share */
  printf("SHARE_INIT\n");
  share = curl_share_init();
  if(!share) {
    fprintf(stderr, "curl_share_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  if(CURLSHE_OK == scode) {
    printf("CURLSHOPT_LOCKFUNC\n");
    scode = curl_share_setopt(share, CURLSHOPT_LOCKFUNC, my_lock);
  }
  if(CURLSHE_OK == scode) {
    printf("CURLSHOPT_UNLOCKFUNC\n");
    scode = curl_share_setopt(share, CURLSHOPT_UNLOCKFUNC, my_unlock);
  }
  if(CURLSHE_OK == scode) {
    printf("CURLSHOPT_USERDATA\n");
    scode = curl_share_setopt(share, CURLSHOPT_USERDATA, &user);
  }
  if(CURLSHE_OK == scode) {
    printf("CURL_LOCK_DATA_SSL_SESSION\n");
    scode = curl_share_setopt(share, CURLSHOPT_SHARE,
                              CURL_LOCK_DATA_SSL_SESSION);
  }

  if(CURLSHE_OK != scode) {
    fprintf(stderr, "curl_share_setopt() failed\n");
    curl_share_cleanup(share);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }


  res = 0;

  /* start treads */
  for(i = 1; i <= THREADS; i++) {

    /* set thread data */
    tdata.url   = URL;
    tdata.share = share;

    /* simulate thread, direct call of "thread" function */
    printf("*** run %d\n",i);
    fire(&tdata);
  }


  /* fetch a another one */
  printf("*** run %d\n", i);
  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_share_cleanup(share);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  url = URL;
  test_setopt(curl, CURLOPT_URL, url);
  printf("CURLOPT_SHARE\n");
  test_setopt(curl, CURLOPT_SHARE, share);

  printf("PERFORM\n");
  curl_easy_perform(curl);

  /* try to free share, expect to fail because share is in use*/
  printf("try SHARE_CLEANUP...\n");
  scode = curl_share_cleanup(share);
  if(scode == CURLSHE_OK) {
    fprintf(stderr, "curl_share_cleanup succeed but error expected\n");
    share = NULL;
  }
  else {
    printf("SHARE_CLEANUP failed, correct\n");
  }

test_cleanup:

  /* clean up last handle */
  printf("CLEANUP\n");
  curl_easy_cleanup(curl);

  /* free share */
  printf("SHARE_CLEANUP\n");
  scode = curl_share_cleanup(share);
  if(scode != CURLSHE_OK)
    fprintf(stderr, "curl_share_cleanup failed, code errno %d\n",
            (int)scode);

  printf("GLOBAL_CLEANUP\n");
  curl_global_cleanup();

  return res;
}