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
struct WildcardData {scalar_t__ state; } ;
struct TYPE_13__ {int /*<<< orphan*/  want; int /*<<< orphan*/  picked; } ;
struct TYPE_12__ {int /*<<< orphan*/  want; int /*<<< orphan*/  picked; } ;
struct TYPE_14__ {int infilesize; scalar_t__ wildcardmatch; TYPE_6__ authproxy; TYPE_5__ authhost; int /*<<< orphan*/  prev_signal; int /*<<< orphan*/  allow_port; void* authproblem; scalar_t__ httpversion; void* errorbuf; void* this_is_a_follow; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_ssl_sessions; } ;
struct TYPE_11__ {scalar_t__ httpreq; int filesize; int postfieldsize; int /*<<< orphan*/  no_signal; scalar_t__ postfields; int /*<<< orphan*/  proxyauth; int /*<<< orphan*/  httpauth; scalar_t__ followlocation; scalar_t__ wildcard_enabled; TYPE_1__ general_ssl; int /*<<< orphan*/ ** str; scalar_t__ uh; } ;
struct TYPE_10__ {scalar_t__ resolve; scalar_t__ cookielist; int /*<<< orphan*/ * url; void* url_alloc; } ;
struct TYPE_9__ {int /*<<< orphan*/ * wouldredirect; } ;
struct Curl_easy {TYPE_7__ state; struct WildcardData wildcard; TYPE_4__ set; TYPE_3__ change; TYPE_2__ info; } ;
typedef  int curl_off_t ;
typedef  scalar_t__ CURLcode ;
typedef  scalar_t__ CURLUcode ;

/* Variables and functions */
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 scalar_t__ CURLWC_INIT ; 
 int /*<<< orphan*/  Curl_cookie_loadfiles (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_http2_init_state (TYPE_7__*) ; 
 int /*<<< orphan*/  Curl_initinfo (struct Curl_easy*) ; 
 scalar_t__ Curl_loadhostpairs (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_pgrsResetTransferSizes (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_pgrsStartNow (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_ssl_initsessions (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_wildcard_init (struct WildcardData*) ; 
 void* FALSE ; 
 scalar_t__ HTTPREQ_GET ; 
 scalar_t__ HTTPREQ_HEAD ; 
 scalar_t__ HTTPREQ_PUT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 size_t STRING_SET_URL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ curl_url_get (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__) ; 

CURLcode Curl_pretransfer(struct Curl_easy *data)
{
  CURLcode result;

  if(!data->change.url && !data->set.uh) {
    /* we can't do anything without URL */
    failf(data, "No URL set!");
    return CURLE_URL_MALFORMAT;
  }

  /* since the URL may have been redirected in a previous use of this handle */
  if(data->change.url_alloc) {
    /* the already set URL is allocated, free it first! */
    Curl_safefree(data->change.url);
    data->change.url_alloc = FALSE;
  }

  if(!data->change.url && data->set.uh) {
    CURLUcode uc;
    uc = curl_url_get(data->set.uh,
                        CURLUPART_URL, &data->set.str[STRING_SET_URL], 0);
    if(uc) {
      failf(data, "No URL set!");
      return CURLE_URL_MALFORMAT;
    }
  }

  data->change.url = data->set.str[STRING_SET_URL];

  /* Init the SSL session ID cache here. We do it here since we want to do it
     after the *_setopt() calls (that could specify the size of the cache) but
     before any transfer takes place. */
  result = Curl_ssl_initsessions(data, data->set.general_ssl.max_ssl_sessions);
  if(result)
    return result;

  data->state.wildcardmatch = data->set.wildcard_enabled;
  data->set.followlocation = 0; /* reset the location-follow counter */
  data->state.this_is_a_follow = FALSE; /* reset this */
  data->state.errorbuf = FALSE; /* no error has occurred */
  data->state.httpversion = 0; /* don't assume any particular server version */

  data->state.authproblem = FALSE;
  data->state.authhost.want = data->set.httpauth;
  data->state.authproxy.want = data->set.proxyauth;
  Curl_safefree(data->info.wouldredirect);
  data->info.wouldredirect = NULL;

  if(data->set.httpreq == HTTPREQ_PUT)
    data->state.infilesize = data->set.filesize;
  else if((data->set.httpreq != HTTPREQ_GET) &&
          (data->set.httpreq != HTTPREQ_HEAD)) {
    data->state.infilesize = data->set.postfieldsize;
    if(data->set.postfields && (data->state.infilesize == -1))
      data->state.infilesize = (curl_off_t)strlen(data->set.postfields);
  }
  else
    data->state.infilesize = 0;

  /* If there is a list of cookie files to read, do it now! */
  if(data->change.cookielist)
    Curl_cookie_loadfiles(data);

  /* If there is a list of host pairs to deal with */
  if(data->change.resolve)
    result = Curl_loadhostpairs(data);

  if(!result) {
    /* Allow data->set.use_port to set which port to use. This needs to be
     * disabled for example when we follow Location: headers to URLs using
     * different ports! */
    data->state.allow_port = TRUE;

#if defined(HAVE_SIGNAL) && defined(SIGPIPE) && !defined(HAVE_MSG_NOSIGNAL)
    /*************************************************************
     * Tell signal handler to ignore SIGPIPE
     *************************************************************/
    if(!data->set.no_signal)
      data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
#endif

    Curl_initinfo(data); /* reset session-specific information "variables" */
    Curl_pgrsResetTransferSizes(data);
    Curl_pgrsStartNow(data);

    /* In case the handle is re-used and an authentication method was picked
       in the session we need to make sure we only use the one(s) we now
       consider to be fine */
    data->state.authhost.picked &= data->state.authhost.want;
    data->state.authproxy.picked &= data->state.authproxy.want;

#ifndef CURL_DISABLE_FTP
    if(data->state.wildcardmatch) {
      struct WildcardData *wc = &data->wildcard;
      if(wc->state < CURLWC_INIT) {
        result = Curl_wildcard_init(wc); /* init wildcard structures */
        if(result)
          return CURLE_OUT_OF_MEMORY;
      }
    }
#endif
    Curl_http2_init_state(&data->state);
  }

  return result;
}