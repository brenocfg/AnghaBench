#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ authneg; int /*<<< orphan*/  rewindaftersend; scalar_t__ proxy_user_passwd; scalar_t__ user_passwd; } ;
struct connectdata {int httpversion; TYPE_1__ bits; struct Curl_easy* data; scalar_t__ oauth_bearer; } ;
struct TYPE_11__ {int httpcode; void* newurl; } ;
struct TYPE_12__ {scalar_t__ picked; void* done; } ;
struct TYPE_10__ {TYPE_6__ authhost; void* authproblem; TYPE_6__ authproxy; } ;
struct TYPE_9__ {int /*<<< orphan*/  url; } ;
struct TYPE_8__ {scalar_t__ httpreq; int /*<<< orphan*/  httpversion; scalar_t__ http_fail_on_error; } ;
struct Curl_easy {TYPE_5__ req; TYPE_4__ state; TYPE_3__ change; TYPE_2__ set; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 unsigned long CURLAUTH_BEARER ; 
 scalar_t__ CURLAUTH_NTLM ; 
 scalar_t__ CURLE_HTTP_RETURNED_ERROR ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURL_HTTP_VERSION_1_1 ; 
 int /*<<< orphan*/  Curl_safefree (void*) ; 
 int FALSE ; 
 scalar_t__ HTTPREQ_GET ; 
 scalar_t__ HTTPREQ_HEAD ; 
 void* TRUE ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 scalar_t__ http_perhapsrewind (struct connectdata*) ; 
 scalar_t__ http_should_fail (struct connectdata*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int pickoneauth (TYPE_6__*,unsigned long) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

CURLcode Curl_http_auth_act(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  bool pickhost = FALSE;
  bool pickproxy = FALSE;
  CURLcode result = CURLE_OK;
  unsigned long authmask = ~0ul;

  if(!conn->oauth_bearer)
    authmask &= (unsigned long)~CURLAUTH_BEARER;

  if(100 <= data->req.httpcode && 199 >= data->req.httpcode)
    /* this is a transient response code, ignore */
    return CURLE_OK;

  if(data->state.authproblem)
    return data->set.http_fail_on_error?CURLE_HTTP_RETURNED_ERROR:CURLE_OK;

  if((conn->bits.user_passwd || conn->oauth_bearer) &&
     ((data->req.httpcode == 401) ||
      (conn->bits.authneg && data->req.httpcode < 300))) {
    pickhost = pickoneauth(&data->state.authhost, authmask);
    if(!pickhost)
      data->state.authproblem = TRUE;
    if(data->state.authhost.picked == CURLAUTH_NTLM &&
       conn->httpversion > 11) {
      infof(data, "Forcing HTTP/1.1 for NTLM");
      connclose(conn, "Force HTTP/1.1 connection");
      conn->data->set.httpversion = CURL_HTTP_VERSION_1_1;
    }
  }
  if(conn->bits.proxy_user_passwd &&
     ((data->req.httpcode == 407) ||
      (conn->bits.authneg && data->req.httpcode < 300))) {
    pickproxy = pickoneauth(&data->state.authproxy,
                            authmask & ~CURLAUTH_BEARER);
    if(!pickproxy)
      data->state.authproblem = TRUE;
  }

  if(pickhost || pickproxy) {
    if((data->set.httpreq != HTTPREQ_GET) &&
       (data->set.httpreq != HTTPREQ_HEAD) &&
       !conn->bits.rewindaftersend) {
      result = http_perhapsrewind(conn);
      if(result)
        return result;
    }
    /* In case this is GSS auth, the newurl field is already allocated so
       we must make sure to free it before allocating a new one. As figured
       out in bug #2284386 */
    Curl_safefree(data->req.newurl);
    data->req.newurl = strdup(data->change.url); /* clone URL */
    if(!data->req.newurl)
      return CURLE_OUT_OF_MEMORY;
  }
  else if((data->req.httpcode < 300) &&
          (!data->state.authhost.done) &&
          conn->bits.authneg) {
    /* no (known) authentication available,
       authentication is not "done" yet and
       no authentication seems to be required and
       we didn't try HEAD or GET */
    if((data->set.httpreq != HTTPREQ_GET) &&
       (data->set.httpreq != HTTPREQ_HEAD)) {
      data->req.newurl = strdup(data->change.url); /* clone URL */
      if(!data->req.newurl)
        return CURLE_OUT_OF_MEMORY;
      data->state.authhost.done = TRUE;
    }
  }
  if(http_should_fail(conn)) {
    failf(data, "The requested URL returned error: %d",
          data->req.httpcode);
    result = CURLE_HTTP_RETURNED_ERROR;
  }

  return result;
}