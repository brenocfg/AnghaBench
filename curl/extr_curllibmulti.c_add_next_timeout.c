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
typedef  scalar_t__ timediff_t ;
struct time_node {int /*<<< orphan*/  time; } ;
struct curltime {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct curl_llist_element {scalar_t__ ptr; struct curl_llist_element* next; } ;
struct curl_llist {struct curl_llist_element* head; } ;
struct Curl_multi {int /*<<< orphan*/  timetree; } ;
struct TYPE_2__ {int /*<<< orphan*/  timenode; struct curl_llist timeoutlist; struct curltime expiretime; } ;
struct Curl_easy {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  Curl_llist_remove (struct curl_llist*,struct curl_llist_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_splayinsert (struct curltime,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_timediff (int /*<<< orphan*/ ,struct curltime) ; 
 int /*<<< orphan*/  memcpy (struct curltime*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static CURLMcode add_next_timeout(struct curltime now,
                                  struct Curl_multi *multi,
                                  struct Curl_easy *d)
{
  struct curltime *tv = &d->state.expiretime;
  struct curl_llist *list = &d->state.timeoutlist;
  struct curl_llist_element *e;
  struct time_node *node = NULL;

  /* move over the timeout list for this specific handle and remove all
     timeouts that are now passed tense and store the next pending
     timeout in *tv */
  for(e = list->head; e;) {
    struct curl_llist_element *n = e->next;
    timediff_t diff;
    node = (struct time_node *)e->ptr;
    diff = Curl_timediff(node->time, now);
    if(diff <= 0)
      /* remove outdated entry */
      Curl_llist_remove(list, e, NULL);
    else
      /* the list is sorted so get out on the first mismatch */
      break;
    e = n;
  }
  e = list->head;
  if(!e) {
    /* clear the expire times within the handles that we remove from the
       splay tree */
    tv->tv_sec = 0;
    tv->tv_usec = 0;
  }
  else {
    /* copy the first entry to 'tv' */
    memcpy(tv, &node->time, sizeof(*tv));

    /* Insert this node again into the splay.  Keep the timer in the list in
       case we need to recompute future timers. */
    multi->timetree = Curl_splayinsert(*tv, multi->timetree,
                                       &d->state.timenode);
  }
  return CURLM_OK;
}