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
struct time_node {scalar_t__ eid; } ;
struct curl_llist_element {scalar_t__ ptr; struct curl_llist_element* next; } ;
struct curl_llist {struct curl_llist_element* head; } ;
struct TYPE_2__ {struct curl_llist timeoutlist; } ;
struct Curl_easy {TYPE_1__ state; } ;
typedef  scalar_t__ expire_id ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (struct curl_llist*,struct curl_llist_element*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
multi_deltimeout(struct Curl_easy *data, expire_id eid)
{
  struct curl_llist_element *e;
  struct curl_llist *timeoutlist = &data->state.timeoutlist;
  /* find and remove the specific node from the list */
  for(e = timeoutlist->head; e; e = e->next) {
    struct time_node *n = (struct time_node *)e->ptr;
    if(n->eid == eid) {
      Curl_llist_remove(timeoutlist, e, NULL);
      return;
    }
  }
}