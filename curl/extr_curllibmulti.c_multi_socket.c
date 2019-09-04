#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct curltime {int dummy; } ;
struct curl_llist_element {scalar_t__ ptr; struct curl_llist_element* next; } ;
struct curl_llist {struct curl_llist_element* head; } ;
struct Curl_tree {struct Curl_easy* payload; } ;
struct Curl_sh_entry {struct curl_llist list; } ;
struct Curl_multi {int num_alive; int /*<<< orphan*/  timetree; int /*<<< orphan*/  timer_lastcall; int /*<<< orphan*/  sockhash; struct Curl_easy* easyp; } ;
struct Curl_easy {scalar_t__ magic; TYPE_2__* conn; struct Curl_easy* next; } ;
typedef  scalar_t__ curl_socket_t ;
struct TYPE_4__ {int cselect_bits; TYPE_1__* handler; } ;
struct TYPE_3__ {int flags; } ;
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
 scalar_t__ CURLEASY_MAGIC_NUMBER ; 
 scalar_t__ CURLM_BAD_HANDLE ; 
 scalar_t__ CURLM_INTERNAL_ERROR ; 
 scalar_t__ CURLM_OK ; 
 scalar_t__ CURL_SOCKET_TIMEOUT ; 
 struct curltime Curl_now () ; 
 int /*<<< orphan*/  Curl_splaygetbest (struct curltime,int /*<<< orphan*/ ,struct Curl_tree**) ; 
 int PROTOPT_DIRLOCK ; 
 int /*<<< orphan*/  SIGPIPE_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_timeout (struct curltime,struct Curl_multi*,struct Curl_easy*) ; 
 scalar_t__ curl_multi_perform (struct Curl_multi*,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ multi_runsingle (struct Curl_multi*,struct curltime,struct Curl_easy*) ; 
 int /*<<< orphan*/  pipe_st ; 
 struct Curl_sh_entry* sh_getentry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sigpipe_ignore (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigpipe_restore (int /*<<< orphan*/ *) ; 
 scalar_t__ singlesocket (struct Curl_multi*,struct Curl_easy*) ; 

__attribute__((used)) static CURLMcode multi_socket(struct Curl_multi *multi,
                              bool checkall,
                              curl_socket_t s,
                              int ev_bitmask,
                              int *running_handles)
{
  CURLMcode result = CURLM_OK;
  struct Curl_easy *data = NULL;
  struct Curl_tree *t;
  struct curltime now = Curl_now();

  if(checkall) {
    /* *perform() deals with running_handles on its own */
    result = curl_multi_perform(multi, running_handles);

    /* walk through each easy handle and do the socket state change magic
       and callbacks */
    if(result != CURLM_BAD_HANDLE) {
      data = multi->easyp;
      while(data && !result) {
        result = singlesocket(multi, data);
        data = data->next;
      }
    }

    /* or should we fall-through and do the timer-based stuff? */
    return result;
  }
  if(s != CURL_SOCKET_TIMEOUT) {

    struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);

    if(!entry)
      /* Unmatched socket, we can't act on it but we ignore this fact.  In
         real-world tests it has been proved that libevent can in fact give
         the application actions even though the socket was just previously
         asked to get removed, so thus we better survive stray socket actions
         and just move on. */
      ;
    else {
      struct curl_llist *list = &entry->list;
      struct curl_llist_element *e;
      SIGPIPE_VARIABLE(pipe_st);

      /* the socket can be shared by many transfers, iterate */
      for(e = list->head; e; e = e->next) {
        data = (struct Curl_easy *)e->ptr;

        if(data->magic != CURLEASY_MAGIC_NUMBER)
          /* bad bad bad bad bad bad bad */
          return CURLM_INTERNAL_ERROR;

        if(data->conn && !(data->conn->handler->flags & PROTOPT_DIRLOCK))
          /* set socket event bitmask if they're not locked */
          data->conn->cselect_bits = ev_bitmask;

        sigpipe_ignore(data, &pipe_st);
        result = multi_runsingle(multi, now, data);
        sigpipe_restore(&pipe_st);

        if(data->conn && !(data->conn->handler->flags & PROTOPT_DIRLOCK))
          /* clear the bitmask only if not locked */
          data->conn->cselect_bits = 0;

        if(CURLM_OK >= result) {
          /* get the socket(s) and check if the state has been changed since
             last */
          result = singlesocket(multi, data);
          if(result)
            return result;
        }
      }

      /* Now we fall-through and do the timer-based stuff, since we don't want
         to force the user to have to deal with timeouts as long as at least
         one connection in fact has traffic. */

      data = NULL; /* set data to NULL again to avoid calling
                      multi_runsingle() in case there's no need to */
      now = Curl_now(); /* get a newer time since the multi_runsingle() loop
                           may have taken some time */
    }
  }
  else {
    /* Asked to run due to time-out. Clear the 'lastcall' variable to force
       update_timer() to trigger a callback to the app again even if the same
       timeout is still the one to run after this call. That handles the case
       when the application asks libcurl to run the timeout prematurely. */
    memset(&multi->timer_lastcall, 0, sizeof(multi->timer_lastcall));
  }

  /*
   * The loop following here will go on as long as there are expire-times left
   * to process in the splay and 'data' will be re-assigned for every expired
   * handle we deal with.
   */
  do {
    /* the first loop lap 'data' can be NULL */
    if(data) {
      SIGPIPE_VARIABLE(pipe_st);

      sigpipe_ignore(data, &pipe_st);
      result = multi_runsingle(multi, now, data);
      sigpipe_restore(&pipe_st);

      if(CURLM_OK >= result) {
        /* get the socket(s) and check if the state has been changed since
           last */
        result = singlesocket(multi, data);
        if(result)
          return result;
      }
    }

    /* Check if there's one (more) expired timer to deal with! This function
       extracts a matching node if there is one */

    multi->timetree = Curl_splaygetbest(now, multi->timetree, &t);
    if(t) {
      data = t->payload; /* assign this for next loop */
      (void)add_next_timeout(now, multi, t->payload);
    }

  } while(t);

  *running_handles = multi->num_alive;
  return result;
}