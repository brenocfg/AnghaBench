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
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ tunnel_proxy; scalar_t__ netrc; scalar_t__ httpproxy; scalar_t__ user_passwd; scalar_t__ proxy_user_passwd; } ;
struct connectdata {TYPE_4__ host; TYPE_1__ bits; scalar_t__ oauth_bearer; struct Curl_easy* data; } ;
struct auth {void* done; scalar_t__ want; scalar_t__ picked; } ;
struct TYPE_7__ {int /*<<< orphan*/  first_host; int /*<<< orphan*/  this_is_a_follow; struct auth authproxy; struct auth authhost; } ;
struct TYPE_6__ {scalar_t__ allow_auth_to_other_hosts; } ;
struct Curl_easy {TYPE_3__ state; TYPE_2__ set; } ;
typedef  scalar_t__ bit ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  DEBUGASSERT (struct Curl_easy*) ; 
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ output_auth_headers (struct connectdata*,struct auth*,char const*,char const*,void*) ; 
 scalar_t__ strcasecompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CURLcode
Curl_http_output_auth(struct connectdata *conn,
                      const char *request,
                      const char *path,
                      bool proxytunnel) /* TRUE if this is the request setting
                                           up the proxy tunnel */
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct auth *authhost;
  struct auth *authproxy;

  DEBUGASSERT(data);

  authhost = &data->state.authhost;
  authproxy = &data->state.authproxy;

  if((conn->bits.httpproxy && conn->bits.proxy_user_passwd) ||
     conn->bits.user_passwd || conn->oauth_bearer)
    /* continue please */;
  else {
    authhost->done = TRUE;
    authproxy->done = TRUE;
    return CURLE_OK; /* no authentication with no user or password */
  }

  if(authhost->want && !authhost->picked)
    /* The app has selected one or more methods, but none has been picked
       so far by a server round-trip. Then we set the picked one to the
       want one, and if this is one single bit it'll be used instantly. */
    authhost->picked = authhost->want;

  if(authproxy->want && !authproxy->picked)
    /* The app has selected one or more methods, but none has been picked so
       far by a proxy round-trip. Then we set the picked one to the want one,
       and if this is one single bit it'll be used instantly. */
    authproxy->picked = authproxy->want;

#ifndef CURL_DISABLE_PROXY
  /* Send proxy authentication header if needed */
  if(conn->bits.httpproxy &&
     (conn->bits.tunnel_proxy == (bit)proxytunnel)) {
    result = output_auth_headers(conn, authproxy, request, path, TRUE);
    if(result)
      return result;
  }
  else
#else
  (void)proxytunnel;
#endif /* CURL_DISABLE_PROXY */
    /* we have no proxy so let's pretend we're done authenticating
       with it */
    authproxy->done = TRUE;

  /* To prevent the user+password to get sent to other than the original
     host due to a location-follow, we do some weirdo checks here */
  if(!data->state.this_is_a_follow ||
     conn->bits.netrc ||
     !data->state.first_host ||
     data->set.allow_auth_to_other_hosts ||
     strcasecompare(data->state.first_host, conn->host.name)) {
    result = output_auth_headers(conn, authhost, request, path, FALSE);
  }
  else
    authhost->done = TRUE;

  return result;
}