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
struct curltime {int dummy; } ;
struct Curl_tree {int /*<<< orphan*/  payload; } ;
struct Curl_multi {int num_alive; int /*<<< orphan*/  timetree; struct Curl_easy* easyp; scalar_t__ in_callback; } ;
struct Curl_easy {struct Curl_easy* next; } ;
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
 scalar_t__ CURLM_BAD_HANDLE ; 
 scalar_t__ CURLM_OK ; 
 scalar_t__ CURLM_RECURSIVE_API_CALL ; 
 struct curltime Curl_now () ; 
 int /*<<< orphan*/  Curl_splaygetbest (struct curltime,int /*<<< orphan*/ ,struct Curl_tree**) ; 
 int /*<<< orphan*/  Curl_update_timer (struct Curl_multi*) ; 
 int /*<<< orphan*/  GOOD_MULTI_HANDLE (struct Curl_multi*) ; 
 int /*<<< orphan*/  SIGPIPE_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_timeout (struct curltime,struct Curl_multi*,int /*<<< orphan*/ ) ; 
 scalar_t__ multi_runsingle (struct Curl_multi*,struct curltime,struct Curl_easy*) ; 
 int /*<<< orphan*/  pipe_st ; 
 int /*<<< orphan*/  sigpipe_ignore (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigpipe_restore (int /*<<< orphan*/ *) ; 

CURLMcode curl_multi_perform(struct Curl_multi *multi, int *running_handles)
{
  struct Curl_easy *data;
  CURLMcode returncode = CURLM_OK;
  struct Curl_tree *t;
  struct curltime now = Curl_now();

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  if(multi->in_callback)
    return CURLM_RECURSIVE_API_CALL;

  data = multi->easyp;
  while(data) {
    CURLMcode result;
    SIGPIPE_VARIABLE(pipe_st);

    sigpipe_ignore(data, &pipe_st);
    result = multi_runsingle(multi, now, data);
    sigpipe_restore(&pipe_st);

    if(result)
      returncode = result;

    data = data->next; /* operate on next handle */
  }

  /*
   * Simply remove all expired timers from the splay since handles are dealt
   * with unconditionally by this function and curl_multi_timeout() requires
   * that already passed/handled expire times are removed from the splay.
   *
   * It is important that the 'now' value is set at the entry of this function
   * and not for the current time as it may have ticked a little while since
   * then and then we risk this loop to remove timers that actually have not
   * been handled!
   */
  do {
    multi->timetree = Curl_splaygetbest(now, multi->timetree, &t);
    if(t)
      /* the removed may have another timeout in queue */
      (void)add_next_timeout(now, multi, t->payload);

  } while(t);

  *running_handles = multi->num_alive;

  if(CURLM_OK >= returncode)
    Curl_update_timer(multi);

  return returncode;
}