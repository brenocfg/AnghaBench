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
struct initurl {char* url; int threadno; int /*<<< orphan*/ * share; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  CURLSH ;

/* Variables and functions */
 int /*<<< orphan*/  CURLSHOPT_LOCKFUNC ; 
 int /*<<< orphan*/  CURLSHOPT_SHARE ; 
 int /*<<< orphan*/  CURLSHOPT_UNLOCKFUNC ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_CONNECT ; 
 int NUM_THREADS ; 
 char* URL ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_share_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_share_init () ; 
 int /*<<< orphan*/  curl_share_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  init_locks () ; 
 int /*<<< orphan*/  kill_locks () ; 
 int /*<<< orphan*/  lock_cb ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct initurl*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_thread ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlock_cb ; 

int main(void)
{
  pthread_t tid[NUM_THREADS];
  int i;
  CURLSH *share;
  struct initurl url[NUM_THREADS];

  /* Must initialize libcurl before any threads are started */
  curl_global_init(CURL_GLOBAL_ALL);

  share = curl_share_init();
  curl_share_setopt(share, CURLSHOPT_LOCKFUNC, lock_cb);
  curl_share_setopt(share, CURLSHOPT_UNLOCKFUNC, unlock_cb);
  curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_CONNECT);

  init_locks();

  for(i = 0; i< NUM_THREADS; i++) {
    int error;
    url[i].url = URL;
    url[i].share = share;
    url[i].threadno = i;
    error = pthread_create(&tid[i], NULL, run_thread, &url[i]);
    if(0 != error)
      fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
    else
      fprintf(stderr, "Thread %d, gets %s\n", i, URL);
  }

  /* now wait for all threads to terminate */
  for(i = 0; i< NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
    fprintf(stderr, "Thread %d terminated\n", i);
  }

  kill_locks();

  curl_share_cleanup(share);
  curl_global_cleanup();
  return 0;
}