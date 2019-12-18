#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct CURLMsg {scalar_t__ msg; int /*<<< orphan*/ * easy_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  memory; } ;
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_PIPELINING ; 
 int /*<<< orphan*/  CURLMOPT_PUSHDATA ; 
 int /*<<< orphan*/  CURLMOPT_PUSHFUNCTION ; 
 scalar_t__ CURLMSG_DONE ; 
 int* CURLPIPE_MULTIPLEX ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 struct CURLMsg* curl_multi_info_read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 scalar_t__ curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ curl_multi_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int pushindex ; 
 int* server_push_callback ; 
 int /*<<< orphan*/  setup (int /*<<< orphan*/ *) ; 

int main(void)
{
  CURL *easy;
  CURLM *multi;
  int still_running; /* keep number of running handles */
  int transfers = 1; /* we start with one */
  int i;
  struct CURLMsg *m;

  /* init a multi stack */
  multi = curl_multi_init();

  easy = curl_easy_init();

  /* set options */
  setup(easy);

  /* add the easy transfer */
  curl_multi_add_handle(multi, easy);

  curl_multi_setopt(multi, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);
  curl_multi_setopt(multi, CURLMOPT_PUSHFUNCTION, server_push_callback);
  curl_multi_setopt(multi, CURLMOPT_PUSHDATA, &transfers);

  while(transfers) {
    int rc;
    CURLMcode mcode = curl_multi_perform(multi, &still_running);
    if(mcode)
      break;

    mcode = curl_multi_wait(multi, NULL, 0, 1000, &rc);
    if(mcode)
      break;


    /*
     * When doing server push, libcurl itself created and added one or more
     * easy handles but *we* need to clean them up when they are done.
     */
    do {
      int msgq = 0;;
      m = curl_multi_info_read(multi, &msgq);
      if(m && (m->msg == CURLMSG_DONE)) {
        CURL *e = m->easy_handle;
        transfers--;
        curl_multi_remove_handle(multi, e);
        curl_easy_cleanup(e);
      }
    } while(m);

  }


  curl_multi_cleanup(multi);

  /* 'pushindex' is now the number of received transfers */
  for(i = 0; i < pushindex; i++) {
    /* do something fun with the data, and then free it when done */
    free(files[i].memory);
  }

  return 0;
}