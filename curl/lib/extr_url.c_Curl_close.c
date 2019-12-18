#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct Curl_multi {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  headers; TYPE_7__* probe; } ;
struct TYPE_18__ {TYPE_8__ doh; struct Curl_easy* newurl; } ;
struct TYPE_13__ {int /*<<< orphan*/  resolver; int /*<<< orphan*/ * ulbuf; int /*<<< orphan*/ * headerbuff; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * scratch; int /*<<< orphan*/ * first_host; struct Curl_easy* range; scalar_t__ rangestringalloc; int /*<<< orphan*/  timeoutlist; } ;
struct TYPE_12__ {int /*<<< orphan*/ * wouldredirect; int /*<<< orphan*/ * contenttype; } ;
struct TYPE_11__ {int /*<<< orphan*/ * str; } ;
struct TYPE_10__ {int /*<<< orphan*/ * referer; scalar_t__ referer_alloc; } ;
struct Curl_easy {int /*<<< orphan*/  wildcard; TYPE_9__ req; TYPE_5__* share; TYPE_4__ state; TYPE_3__ info; int /*<<< orphan*/ * asi; TYPE_2__ set; TYPE_1__ change; scalar_t__ magic; int /*<<< orphan*/ * multi_easy; struct Curl_multi* multi; } ;
struct TYPE_15__ {struct Curl_easy* memory; } ;
struct TYPE_16__ {TYPE_6__ serverdoh; } ;
struct TYPE_14__ {int /*<<< orphan*/  dirty; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_SHARE ; 
 int /*<<< orphan*/  Curl_altsvc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_altsvc_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_convert_close (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_expire_clear (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_flush_cookies (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_free_request_state (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_freeset (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_http2_cleanup_dependencies (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_http_auth_cleanup_digest (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_resolver_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_share_lock (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_unlock (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_ssl_close_all (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_ssl_free_certinfo (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_wildcard_dtor (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 size_t STRING_ALTSVC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (struct Curl_multi*,struct Curl_easy*) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct Curl_easy*) ; 
 int /*<<< orphan*/  up_free (struct Curl_easy*) ; 

CURLcode Curl_close(struct Curl_easy **datap)
{
  struct Curl_multi *m;
  struct Curl_easy *data;

  if(!datap || !*datap)
    return CURLE_OK;

  data = *datap;
  *datap = NULL;

  Curl_expire_clear(data); /* shut off timers */

  m = data->multi;
  if(m)
    /* This handle is still part of a multi handle, take care of this first
       and detach this handle from there. */
    curl_multi_remove_handle(data->multi, data);

  if(data->multi_easy) {
    /* when curl_easy_perform() is used, it creates its own multi handle to
       use and this is the one */
    curl_multi_cleanup(data->multi_easy);
    data->multi_easy = NULL;
  }

  /* Destroy the timeout list that is held in the easy handle. It is
     /normally/ done by curl_multi_remove_handle() but this is "just in
     case" */
  Curl_llist_destroy(&data->state.timeoutlist, NULL);

  data->magic = 0; /* force a clear AFTER the possibly enforced removal from
                      the multi handle, since that function uses the magic
                      field! */

  if(data->state.rangestringalloc)
    free(data->state.range);

  /* freed here just in case DONE wasn't called */
  Curl_free_request_state(data);

  /* Close down all open SSL info and sessions */
  Curl_ssl_close_all(data);
  Curl_safefree(data->state.first_host);
  Curl_safefree(data->state.scratch);
  Curl_ssl_free_certinfo(data);

  /* Cleanup possible redirect junk */
  free(data->req.newurl);
  data->req.newurl = NULL;

  if(data->change.referer_alloc) {
    Curl_safefree(data->change.referer);
    data->change.referer_alloc = FALSE;
  }
  data->change.referer = NULL;

  up_free(data);
  Curl_safefree(data->state.buffer);
  Curl_safefree(data->state.headerbuff);
  Curl_safefree(data->state.ulbuf);
  Curl_flush_cookies(data, TRUE);
#ifdef USE_ALTSVC
  Curl_altsvc_save(data->asi, data->set.str[STRING_ALTSVC]);
  Curl_altsvc_cleanup(data->asi);
  data->asi = NULL;
#endif
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_CRYPTO_AUTH)
  Curl_http_auth_cleanup_digest(data);
#endif
  Curl_safefree(data->info.contenttype);
  Curl_safefree(data->info.wouldredirect);

  /* this destroys the channel and we cannot use it anymore after this */
  Curl_resolver_cleanup(data->state.resolver);

  Curl_http2_cleanup_dependencies(data);
  Curl_convert_close(data);

  /* No longer a dirty share, if it exists */
  if(data->share) {
    Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);
    data->share->dirty--;
    Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);
  }

#ifndef CURL_DISABLE_DOH
  free(data->req.doh.probe[0].serverdoh.memory);
  free(data->req.doh.probe[1].serverdoh.memory);
  curl_slist_free_all(data->req.doh.headers);
#endif

  /* destruct wildcard structures if it is needed */
  Curl_wildcard_dtor(&data->wildcard);
  Curl_freeset(data);
  free(data);
  return CURLE_OK;
}