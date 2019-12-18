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
struct curltime {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct curl_llist {scalar_t__ size; int /*<<< orphan*/  tail; } ;
struct Curl_multi {int /*<<< orphan*/  timetree; } ;
struct TYPE_2__ {int /*<<< orphan*/  timenode; struct curl_llist timeoutlist; struct curltime expiretime; } ;
struct Curl_easy {TYPE_1__ state; struct Curl_multi* multi; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (struct curl_llist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int Curl_splayremovebyaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 

void Curl_expire_clear(struct Curl_easy *data)
{
  struct Curl_multi *multi = data->multi;
  struct curltime *nowp = &data->state.expiretime;

  /* this is only interesting while there is still an associated multi struct
     remaining! */
  if(!multi)
    return;

  if(nowp->tv_sec || nowp->tv_usec) {
    /* Since this is an cleared time, we must remove the previous entry from
       the splay tree */
    struct curl_llist *list = &data->state.timeoutlist;
    int rc;

    rc = Curl_splayremovebyaddr(multi->timetree,
                                &data->state.timenode,
                                &multi->timetree);
    if(rc)
      infof(data, "Internal error clearing splay node = %d\n", rc);

    /* flush the timeout list too */
    while(list->size > 0) {
      Curl_llist_remove(list, list->tail, NULL);
    }

#ifdef DEBUGBUILD
    infof(data, "Expire cleared (transfer %p)\n", data);
#endif
    nowp->tv_sec = 0;
    nowp->tv_usec = 0;
  }
}