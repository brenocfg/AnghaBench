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
struct TYPE_12__ {TYPE_4__* closure_handle; } ;
struct Curl_multi {int /*<<< orphan*/  timer_lastcall; int /*<<< orphan*/  num_alive; int /*<<< orphan*/  num_easy; struct Curl_easy* easyp; struct Curl_easy* easylp; int /*<<< orphan*/  psl; TYPE_5__ conn_cache; int /*<<< orphan*/  hostcache; scalar_t__ in_callback; } ;
struct TYPE_14__ {int /*<<< orphan*/  no_signal; int /*<<< orphan*/  server_response_timeout; int /*<<< orphan*/  timeout; scalar_t__* errorbuffer; } ;
struct TYPE_13__ {TYPE_5__* conn_cache; int /*<<< orphan*/  timeoutlist; } ;
struct TYPE_8__ {scalar_t__ hostcachetype; int /*<<< orphan*/ * hostcache; } ;
struct Curl_easy {TYPE_7__ set; TYPE_6__ state; struct Curl_multi* multi; struct Curl_easy* prev; struct Curl_easy* next; int /*<<< orphan*/ * psl; TYPE_2__* share; TYPE_1__ dns; } ;
struct TYPE_10__ {int /*<<< orphan*/  no_signal; int /*<<< orphan*/  server_response_timeout; int /*<<< orphan*/  timeout; } ;
struct TYPE_11__ {TYPE_3__ set; } ;
struct TYPE_9__ {int specifier; int /*<<< orphan*/  psl; TYPE_5__ conn_cache; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_ADDED_ALREADY ; 
 int /*<<< orphan*/  CURLM_BAD_EASY_HANDLE ; 
 int /*<<< orphan*/  CURLM_BAD_HANDLE ; 
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  CURLM_RECURSIVE_API_CALL ; 
 int /*<<< orphan*/  CURLM_STATE_INIT ; 
 int CURL_LOCK_DATA_CONNECT ; 
 int CURL_LOCK_DATA_PSL ; 
 int /*<<< orphan*/  Curl_expire (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_llist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_update_timer (struct Curl_multi*) ; 
 int /*<<< orphan*/  EXPIRE_RUN_NOW ; 
 int /*<<< orphan*/  GOOD_EASY_HANDLE (struct Curl_easy*) ; 
 int /*<<< orphan*/  GOOD_MULTI_HANDLE (struct Curl_multi*) ; 
 scalar_t__ HCACHE_MULTI ; 
 scalar_t__ HCACHE_NONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multistate (struct Curl_easy*,int /*<<< orphan*/ ) ; 

CURLMcode curl_multi_add_handle(struct Curl_multi *multi,
                                struct Curl_easy *data)
{
  /* First, make some basic checks that the CURLM handle is a good handle */
  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  /* Verify that we got a somewhat good easy handle too */
  if(!GOOD_EASY_HANDLE(data))
    return CURLM_BAD_EASY_HANDLE;

  /* Prevent users from adding same easy handle more than once and prevent
     adding to more than one multi stack */
  if(data->multi)
    return CURLM_ADDED_ALREADY;

  if(multi->in_callback)
    return CURLM_RECURSIVE_API_CALL;

  /* Initialize timeout list for this handle */
  Curl_llist_init(&data->state.timeoutlist, NULL);

  /*
   * No failure allowed in this function beyond this point. And no
   * modification of easy nor multi handle allowed before this except for
   * potential multi's connection cache growing which won't be undone in this
   * function no matter what.
   */
  if(data->set.errorbuffer)
    data->set.errorbuffer[0] = 0;

  /* set the easy handle */
  multistate(data, CURLM_STATE_INIT);

  /* for multi interface connections, we share DNS cache automatically if the
     easy handle's one is currently not set. */
  if(!data->dns.hostcache ||
     (data->dns.hostcachetype == HCACHE_NONE)) {
    data->dns.hostcache = &multi->hostcache;
    data->dns.hostcachetype = HCACHE_MULTI;
  }

  /* Point to the shared or multi handle connection cache */
  if(data->share && (data->share->specifier & (1<< CURL_LOCK_DATA_CONNECT)))
    data->state.conn_cache = &data->share->conn_cache;
  else
    data->state.conn_cache = &multi->conn_cache;

#ifdef USE_LIBPSL
  /* Do the same for PSL. */
  if(data->share && (data->share->specifier & (1 << CURL_LOCK_DATA_PSL)))
    data->psl = &data->share->psl;
  else
    data->psl = &multi->psl;
#endif

  /* We add the new entry last in the list. */
  data->next = NULL; /* end of the line */
  if(multi->easyp) {
    struct Curl_easy *last = multi->easylp;
    last->next = data;
    data->prev = last;
    multi->easylp = data; /* the new last node */
  }
  else {
    /* first node, make prev NULL! */
    data->prev = NULL;
    multi->easylp = multi->easyp = data; /* both first and last */
  }

  /* make the Curl_easy refer back to this multi handle */
  data->multi = multi;

  /* Set the timeout for this handle to expire really soon so that it will
     be taken care of even when this handle is added in the midst of operation
     when only the curl_multi_socket() API is used. During that flow, only
     sockets that time-out or have actions will be dealt with. Since this
     handle has no action yet, we make sure it times out to get things to
     happen. */
  Curl_expire(data, 0, EXPIRE_RUN_NOW);

  /* increase the node-counter */
  multi->num_easy++;

  /* increase the alive-counter */
  multi->num_alive++;

  /* A somewhat crude work-around for a little glitch in Curl_update_timer()
     that happens if the lastcall time is set to the same time when the handle
     is removed as when the next handle is added, as then the check in
     Curl_update_timer() that prevents calling the application multiple times
     with the same timer info will not trigger and then the new handle's
     timeout will not be notified to the app.

     The work-around is thus simply to clear the 'lastcall' variable to force
     Curl_update_timer() to always trigger a callback to the app when a new
     easy handle is added */
  memset(&multi->timer_lastcall, 0, sizeof(multi->timer_lastcall));

  /* The closure handle only ever has default timeouts set. To improve the
     state somewhat we clone the timeouts from each added handle so that the
     closure handle always has the same timeouts as the most recently added
     easy handle. */
  data->state.conn_cache->closure_handle->set.timeout = data->set.timeout;
  data->state.conn_cache->closure_handle->set.server_response_timeout =
    data->set.server_response_timeout;
  data->state.conn_cache->closure_handle->set.no_signal =
    data->set.no_signal;

  Curl_update_timer(multi);
  return CURLM_OK;
}