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
struct curl_llist_element {struct Curl_message* ptr; } ;
struct TYPE_3__ {struct curl_llist_element* head; } ;
struct Curl_multi {TYPE_1__ msglist; int /*<<< orphan*/  in_callback; } ;
struct Curl_message {int /*<<< orphan*/  extmsg; } ;
typedef  int /*<<< orphan*/  CURLMsg ;

/* Variables and functions */
 scalar_t__ Curl_llist_count (TYPE_1__*) ; 
 int /*<<< orphan*/  Curl_llist_remove (TYPE_1__*,struct curl_llist_element*,int /*<<< orphan*/ *) ; 
 scalar_t__ GOOD_MULTI_HANDLE (struct Curl_multi*) ; 
 int curlx_uztosi (scalar_t__) ; 

CURLMsg *curl_multi_info_read(struct Curl_multi *multi, int *msgs_in_queue)
{
  struct Curl_message *msg;

  *msgs_in_queue = 0; /* default to none */

  if(GOOD_MULTI_HANDLE(multi) &&
     !multi->in_callback &&
     Curl_llist_count(&multi->msglist)) {
    /* there is one or more messages in the list */
    struct curl_llist_element *e;

    /* extract the head of the list to return */
    e = multi->msglist.head;

    msg = e->ptr;

    /* remove the extracted entry */
    Curl_llist_remove(&multi->msglist, e, NULL);

    *msgs_in_queue = curlx_uztosi(Curl_llist_count(&multi->msglist));

    return &msg->extmsg;
  }
  return NULL;
}