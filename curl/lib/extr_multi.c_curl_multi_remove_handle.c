#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct curl_llist_element {struct Curl_message* ptr; struct curl_llist_element* next; } ;
struct TYPE_14__ {struct curl_llist_element* head; } ;
struct Curl_multi {int /*<<< orphan*/  num_easy; TYPE_5__* easylp; TYPE_4__* easyp; TYPE_7__ msglist; int /*<<< orphan*/  psl; TYPE_7__ pending; int /*<<< orphan*/  num_alive; scalar_t__ in_callback; } ;
struct TYPE_10__ {struct Curl_easy* easy_handle; } ;
struct Curl_message {TYPE_3__ extmsg; } ;
struct TYPE_9__ {int /*<<< orphan*/ * conn_cache; int /*<<< orphan*/  timeoutlist; } ;
struct TYPE_8__ {scalar_t__ hostcachetype; int /*<<< orphan*/ * hostcache; } ;
struct Curl_easy {scalar_t__ mstate; TYPE_5__* prev; TYPE_4__* next; int /*<<< orphan*/ * multi; int /*<<< orphan*/ * psl; TYPE_6__* conn; TYPE_2__ state; int /*<<< orphan*/  wildcard; TYPE_1__ dns; struct curl_llist_element connect_queue; int /*<<< orphan*/  result; } ;
struct TYPE_13__ {struct Curl_easy* data; } ;
struct TYPE_12__ {TYPE_4__* next; } ;
struct TYPE_11__ {TYPE_5__* prev; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_BAD_EASY_HANDLE ; 
 int /*<<< orphan*/  CURLM_BAD_HANDLE ; 
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  CURLM_RECURSIVE_API_CALL ; 
 scalar_t__ CURLM_STATE_COMPLETED ; 
 scalar_t__ CURLM_STATE_DO ; 
 int /*<<< orphan*/  Curl_expire_clear (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_remove (TYPE_7__*,struct curl_llist_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_update_timer (struct Curl_multi*) ; 
 int /*<<< orphan*/  Curl_wildcard_dtor (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  GOOD_EASY_HANDLE (struct Curl_easy*) ; 
 int /*<<< orphan*/  GOOD_MULTI_HANDLE (struct Curl_multi*) ; 
 scalar_t__ HCACHE_MULTI ; 
 scalar_t__ HCACHE_NONE ; 
 int TRUE ; 
 int /*<<< orphan*/  detach_connnection (struct Curl_easy*) ; 
 int /*<<< orphan*/  multi_done (struct Curl_easy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  singlesocket (struct Curl_multi*,struct Curl_easy*) ; 
 int /*<<< orphan*/  streamclose (TYPE_6__*,char*) ; 

CURLMcode curl_multi_remove_handle(struct Curl_multi *multi,
                                   struct Curl_easy *data)
{
  struct Curl_easy *easy = data;
  bool premature;
  bool easy_owns_conn;
  struct curl_llist_element *e;

  /* First, make some basic checks that the CURLM handle is a good handle */
  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  /* Verify that we got a somewhat good easy handle too */
  if(!GOOD_EASY_HANDLE(data))
    return CURLM_BAD_EASY_HANDLE;

  /* Prevent users from trying to remove same easy handle more than once */
  if(!data->multi)
    return CURLM_OK; /* it is already removed so let's say it is fine! */

  if(multi->in_callback)
    return CURLM_RECURSIVE_API_CALL;

  premature = (data->mstate < CURLM_STATE_COMPLETED) ? TRUE : FALSE;
  easy_owns_conn = (data->conn && (data->conn->data == easy)) ?
    TRUE : FALSE;

  /* If the 'state' is not INIT or COMPLETED, we might need to do something
     nice to put the easy_handle in a good known state when this returns. */
  if(premature) {
    /* this handle is "alive" so we need to count down the total number of
       alive connections when this is removed */
    multi->num_alive--;
  }

  if(data->conn &&
     data->mstate > CURLM_STATE_DO &&
     data->mstate < CURLM_STATE_COMPLETED) {
    /* Set connection owner so that the DONE function closes it.  We can
       safely do this here since connection is killed. */
    data->conn->data = easy;
    streamclose(data->conn, "Removed with partial response");
    easy_owns_conn = TRUE;
  }

  if(data->conn) {

    /* we must call multi_done() here (if we still own the connection) so that
       we don't leave a half-baked one around */
    if(easy_owns_conn) {

      /* multi_done() clears the conn->data field to lose the association
         between the easy handle and the connection

         Note that this ignores the return code simply because there's
         nothing really useful to do with it anyway! */
      (void)multi_done(data, data->result, premature);
    }
  }

  /* The timer must be shut down before data->multi is set to NULL, else the
     timenode will remain in the splay tree after curl_easy_cleanup is
     called. Do it after multi_done() in case that sets another time! */
  Curl_expire_clear(data);

  if(data->connect_queue.ptr)
    /* the handle was in the pending list waiting for an available connection,
       so go ahead and remove it */
    Curl_llist_remove(&multi->pending, &data->connect_queue, NULL);

  if(data->dns.hostcachetype == HCACHE_MULTI) {
    /* stop using the multi handle's DNS cache, *after* the possible
       multi_done() call above */
    data->dns.hostcache = NULL;
    data->dns.hostcachetype = HCACHE_NONE;
  }

  Curl_wildcard_dtor(&data->wildcard);

  /* destroy the timeout list that is held in the easy handle, do this *after*
     multi_done() as that may actually call Curl_expire that uses this */
  Curl_llist_destroy(&data->state.timeoutlist, NULL);

  /* as this was using a shared connection cache we clear the pointer to that
     since we're not part of that multi handle anymore */
  data->state.conn_cache = NULL;

  /* change state without using multistate(), only to make singlesocket() do
     what we want */
  data->mstate = CURLM_STATE_COMPLETED;
  singlesocket(multi, easy); /* to let the application know what sockets that
                                vanish with this handle */

  /* Remove the association between the connection and the handle */
  if(data->conn) {
    data->conn->data = NULL;
    detach_connnection(data);
  }

#ifdef USE_LIBPSL
  /* Remove the PSL association. */
  if(data->psl == &multi->psl)
    data->psl = NULL;
#endif

  data->multi = NULL; /* clear the association to this multi handle */

  /* make sure there's no pending message in the queue sent from this easy
     handle */

  for(e = multi->msglist.head; e; e = e->next) {
    struct Curl_message *msg = e->ptr;

    if(msg->extmsg.easy_handle == easy) {
      Curl_llist_remove(&multi->msglist, e, NULL);
      /* there can only be one from this specific handle */
      break;
    }
  }

  /* make the previous node point to our next */
  if(data->prev)
    data->prev->next = data->next;
  else
    multi->easyp = data->next; /* point to first node */

  /* make our next point to our previous node */
  if(data->next)
    data->next->prev = data->prev;
  else
    multi->easylp = data->prev; /* point to last node */

  /* NOTE NOTE NOTE
     We do not touch the easy handle here! */
  multi->num_easy--; /* one less to care about now */

  Curl_update_timer(multi);
  return CURLM_OK;
}