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
struct Curl_multi {int /*<<< orphan*/  psl; int /*<<< orphan*/  hostcache; int /*<<< orphan*/  pending; int /*<<< orphan*/  msglist; int /*<<< orphan*/  conn_cache; int /*<<< orphan*/  sockhash; struct Curl_easy* easyp; scalar_t__ type; scalar_t__ in_callback; } ;
struct TYPE_4__ {int /*<<< orphan*/ * conn_cache; int /*<<< orphan*/  done; } ;
struct TYPE_3__ {scalar_t__ hostcachetype; int /*<<< orphan*/ * hostcache; } ;
struct Curl_easy {int /*<<< orphan*/ * psl; int /*<<< orphan*/ * multi; TYPE_2__ state; TYPE_1__ dns; scalar_t__ conn; struct Curl_easy* next; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLM_BAD_HANDLE ; 
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  CURLM_RECURSIVE_API_CALL ; 
 int /*<<< orphan*/  Curl_conncache_close_all_connections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_conncache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_hostcache_clean (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_psl_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ GOOD_MULTI_HANDLE (struct Curl_multi*) ; 
 scalar_t__ HCACHE_MULTI ; 
 scalar_t__ HCACHE_NONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (struct Curl_multi*) ; 
 int /*<<< orphan*/  multi_done (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CURLMcode curl_multi_cleanup(struct Curl_multi *multi)
{
  struct Curl_easy *data;
  struct Curl_easy *nextdata;

  if(GOOD_MULTI_HANDLE(multi)) {
    if(multi->in_callback)
      return CURLM_RECURSIVE_API_CALL;

    multi->type = 0; /* not good anymore */

    /* Firsrt remove all remaining easy handles */
    data = multi->easyp;
    while(data) {
      nextdata = data->next;
      if(!data->state.done && data->conn)
        /* if DONE was never called for this handle */
        (void)multi_done(data, CURLE_OK, TRUE);
      if(data->dns.hostcachetype == HCACHE_MULTI) {
        /* clear out the usage of the shared DNS cache */
        Curl_hostcache_clean(data, data->dns.hostcache);
        data->dns.hostcache = NULL;
        data->dns.hostcachetype = HCACHE_NONE;
      }

      /* Clear the pointer to the connection cache */
      data->state.conn_cache = NULL;
      data->multi = NULL; /* clear the association */

#ifdef USE_LIBPSL
      if(data->psl == &multi->psl)
        data->psl = NULL;
#endif

      data = nextdata;
    }

    /* Close all the connections in the connection cache */
    Curl_conncache_close_all_connections(&multi->conn_cache);

    Curl_hash_destroy(&multi->sockhash);
    Curl_conncache_destroy(&multi->conn_cache);
    Curl_llist_destroy(&multi->msglist, NULL);
    Curl_llist_destroy(&multi->pending, NULL);

    Curl_hash_destroy(&multi->hostcache);
    Curl_psl_destroy(&multi->psl);
    free(multi);

    return CURLM_OK;
  }
  return CURLM_BAD_HANDLE;
}