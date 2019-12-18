#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int maxredirs; int followlocation; void* httpreq; int keep_post; int /*<<< orphan*/  opt_no_body; scalar_t__ http_auto_referer; } ;
struct TYPE_7__ {char* wouldredirect; int httpcode; } ;
struct TYPE_6__ {int referer_alloc; char* referer; char* url; int url_alloc; } ;
struct TYPE_5__ {void* allow_port; int /*<<< orphan*/  uh; void* this_is_a_follow; } ;
struct Curl_easy {TYPE_4__ set; TYPE_3__ info; TYPE_2__ change; TYPE_1__ state; } ;
typedef  scalar_t__ followtype ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  scalar_t__ CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_TOO_MANY_REDIRECTS ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 int /*<<< orphan*/  CURLU_NON_SUPPORT_SCHEME ; 
 int /*<<< orphan*/  CURLU_URLENCODE ; 
 int CURL_REDIR_POST_301 ; 
 int CURL_REDIR_POST_302 ; 
 int CURL_REDIR_POST_303 ; 
 scalar_t__ Curl_is_absolute_url (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_pgrsResetTransferSizes (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_pgrsTime (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  Curl_uc_to_curlcode (scalar_t__) ; 
 int /*<<< orphan*/  DEBUGASSERT (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 scalar_t__ FOLLOW_FAKE ; 
 scalar_t__ FOLLOW_REDIR ; 
 void* HTTPREQ_GET ; 
 void* HTTPREQ_POST ; 
 void* HTTPREQ_POST_FORM ; 
 void* HTTPREQ_POST_MIME ; 
 int /*<<< orphan*/  MAX_SCHEME_LEN ; 
 int /*<<< orphan*/  TIMER_REDIRECT ; 
 void* TRUE ; 
 scalar_t__ curl_url_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 void* strdup (char*) ; 

CURLcode Curl_follow(struct Curl_easy *data,
                     char *newurl,    /* the Location: string */
                     followtype type) /* see transfer.h */
{
#ifdef CURL_DISABLE_HTTP
  (void)data;
  (void)newurl;
  (void)type;
  /* Location: following will not happen when HTTP is disabled */
  return CURLE_TOO_MANY_REDIRECTS;
#else

  /* Location: redirect */
  bool disallowport = FALSE;
  bool reachedmax = FALSE;
  CURLUcode uc;

  if(type == FOLLOW_REDIR) {
    if((data->set.maxredirs != -1) &&
       (data->set.followlocation >= data->set.maxredirs)) {
      reachedmax = TRUE;
      type = FOLLOW_FAKE; /* switch to fake to store the would-be-redirected
                             to URL */
    }
    else {
      /* mark the next request as a followed location: */
      data->state.this_is_a_follow = TRUE;

      data->set.followlocation++; /* count location-followers */

      if(data->set.http_auto_referer) {
        /* We are asked to automatically set the previous URL as the referer
           when we get the next URL. We pick the ->url field, which may or may
           not be 100% correct */

        if(data->change.referer_alloc) {
          Curl_safefree(data->change.referer);
          data->change.referer_alloc = FALSE;
        }

        data->change.referer = strdup(data->change.url);
        if(!data->change.referer)
          return CURLE_OUT_OF_MEMORY;
        data->change.referer_alloc = TRUE; /* yes, free this later */
      }
    }
  }

  if(Curl_is_absolute_url(newurl, NULL, MAX_SCHEME_LEN))
    /* This is an absolute URL, don't allow the custom port number */
    disallowport = TRUE;

  DEBUGASSERT(data->state.uh);
  uc = curl_url_set(data->state.uh, CURLUPART_URL, newurl,
                    (type == FOLLOW_FAKE) ? CURLU_NON_SUPPORT_SCHEME :
                    ((type == FOLLOW_REDIR) ? CURLU_URLENCODE : 0) );
  if(uc) {
    if(type != FOLLOW_FAKE)
      return Curl_uc_to_curlcode(uc);

    /* the URL could not be parsed for some reason, but since this is FAKE
       mode, just duplicate the field as-is */
    newurl = strdup(newurl);
    if(!newurl)
      return CURLE_OUT_OF_MEMORY;
  }
  else {

    uc = curl_url_get(data->state.uh, CURLUPART_URL, &newurl, 0);
    if(uc)
      return Curl_uc_to_curlcode(uc);
  }

  if(type == FOLLOW_FAKE) {
    /* we're only figuring out the new url if we would've followed locations
       but now we're done so we can get out! */
    data->info.wouldredirect = newurl;

    if(reachedmax) {
      failf(data, "Maximum (%ld) redirects followed", data->set.maxredirs);
      return CURLE_TOO_MANY_REDIRECTS;
    }
    return CURLE_OK;
  }

  if(disallowport)
    data->state.allow_port = FALSE;

  if(data->change.url_alloc)
    Curl_safefree(data->change.url);

  data->change.url = newurl;
  data->change.url_alloc = TRUE;

  infof(data, "Issue another request to this URL: '%s'\n", data->change.url);

  /*
   * We get here when the HTTP code is 300-399 (and 401). We need to perform
   * differently based on exactly what return code there was.
   *
   * News from 7.10.6: we can also get here on a 401 or 407, in case we act on
   * a HTTP (proxy-) authentication scheme other than Basic.
   */
  switch(data->info.httpcode) {
    /* 401 - Act on a WWW-Authenticate, we keep on moving and do the
       Authorization: XXXX header in the HTTP request code snippet */
    /* 407 - Act on a Proxy-Authenticate, we keep on moving and do the
       Proxy-Authorization: XXXX header in the HTTP request code snippet */
    /* 300 - Multiple Choices */
    /* 306 - Not used */
    /* 307 - Temporary Redirect */
  default:  /* for all above (and the unknown ones) */
    /* Some codes are explicitly mentioned since I've checked RFC2616 and they
     * seem to be OK to POST to.
     */
    break;
  case 301: /* Moved Permanently */
    /* (quote from RFC7231, section 6.4.2)
     *
     * Note: For historical reasons, a user agent MAY change the request
     * method from POST to GET for the subsequent request.  If this
     * behavior is undesired, the 307 (Temporary Redirect) status code
     * can be used instead.
     *
     * ----
     *
     * Many webservers expect this, so these servers often answers to a POST
     * request with an error page. To be sure that libcurl gets the page that
     * most user agents would get, libcurl has to force GET.
     *
     * This behaviour is forbidden by RFC1945 and the obsolete RFC2616, and
     * can be overridden with CURLOPT_POSTREDIR.
     */
    if((data->set.httpreq == HTTPREQ_POST
        || data->set.httpreq == HTTPREQ_POST_FORM
        || data->set.httpreq == HTTPREQ_POST_MIME)
       && !(data->set.keep_post & CURL_REDIR_POST_301)) {
      infof(data, "Switch from POST to GET\n");
      data->set.httpreq = HTTPREQ_GET;
    }
    break;
  case 302: /* Found */
    /* (quote from RFC7231, section 6.4.3)
     *
     * Note: For historical reasons, a user agent MAY change the request
     * method from POST to GET for the subsequent request.  If this
     * behavior is undesired, the 307 (Temporary Redirect) status code
     * can be used instead.
     *
     * ----
     *
     * Many webservers expect this, so these servers often answers to a POST
     * request with an error page. To be sure that libcurl gets the page that
     * most user agents would get, libcurl has to force GET.
     *
     * This behaviour is forbidden by RFC1945 and the obsolete RFC2616, and
     * can be overridden with CURLOPT_POSTREDIR.
     */
    if((data->set.httpreq == HTTPREQ_POST
        || data->set.httpreq == HTTPREQ_POST_FORM
        || data->set.httpreq == HTTPREQ_POST_MIME)
       && !(data->set.keep_post & CURL_REDIR_POST_302)) {
      infof(data, "Switch from POST to GET\n");
      data->set.httpreq = HTTPREQ_GET;
    }
    break;

  case 303: /* See Other */
    /* Disable both types of POSTs, unless the user explicitly
       asks for POST after POST */
    if(data->set.httpreq != HTTPREQ_GET
      && !(data->set.keep_post & CURL_REDIR_POST_303)) {
      data->set.httpreq = HTTPREQ_GET; /* enforce GET request */
      infof(data, "Disables POST, goes with %s\n",
            data->set.opt_no_body?"HEAD":"GET");
    }
    break;
  case 304: /* Not Modified */
    /* 304 means we did a conditional request and it was "Not modified".
     * We shouldn't get any Location: header in this response!
     */
    break;
  case 305: /* Use Proxy */
    /* (quote from RFC2616, section 10.3.6):
     * "The requested resource MUST be accessed through the proxy given
     * by the Location field. The Location field gives the URI of the
     * proxy.  The recipient is expected to repeat this single request
     * via the proxy. 305 responses MUST only be generated by origin
     * servers."
     */
    break;
  }
  Curl_pgrsTime(data, TIMER_REDIRECT);
  Curl_pgrsResetTransferSizes(data);

  return CURLE_OK;
#endif /* CURL_DISABLE_HTTP */
}