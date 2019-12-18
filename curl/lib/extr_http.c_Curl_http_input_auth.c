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
struct connectdata {int /*<<< orphan*/  http_negotiate_state; int /*<<< orphan*/  proxy_negotiate_state; struct Curl_easy* data; } ;
struct auth {unsigned long avail; unsigned long picked; } ;
struct TYPE_8__ {void* authproblem; struct auth authhost; struct auth authproxy; } ;
struct TYPE_7__ {scalar_t__ newurl; } ;
struct TYPE_6__ {int /*<<< orphan*/  url; } ;
struct TYPE_5__ {unsigned long proxyauthavail; unsigned long httpauthavail; } ;
struct Curl_easy {TYPE_4__ state; TYPE_3__ req; TYPE_2__ change; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  curlnegotiate ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 unsigned long CURLAUTH_BASIC ; 
 unsigned long CURLAUTH_BEARER ; 
 unsigned long CURLAUTH_DIGEST ; 
 unsigned long CURLAUTH_NEGOTIATE ; 
 void* CURLAUTH_NONE ; 
 unsigned long CURLAUTH_NTLM ; 
 unsigned long CURLAUTH_NTLM_WB ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ Curl_auth_is_digest_supported () ; 
 scalar_t__ Curl_auth_is_ntlm_supported () ; 
 scalar_t__ Curl_auth_is_spnego_supported () ; 
 scalar_t__ Curl_input_digest (struct connectdata*,int,char const*) ; 
 scalar_t__ Curl_input_negotiate (struct connectdata*,int,char const*) ; 
 scalar_t__ Curl_input_ntlm (struct connectdata*,int,char const*) ; 
 scalar_t__ Curl_input_ntlm_wb (struct connectdata*,int,char const*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 void* FALSE ; 
 int /*<<< orphan*/  GSS_AUTHRECV ; 
 scalar_t__ ISSPACE (char const) ; 
 void* TRUE ; 
 scalar_t__ checkprefix (char*,char const*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 

CURLcode Curl_http_input_auth(struct connectdata *conn, bool proxy,
                              const char *auth) /* the first non-space */
{
  /*
   * This resource requires authentication
   */
  struct Curl_easy *data = conn->data;

#ifdef USE_SPNEGO
  curlnegotiate *negstate = proxy ? &conn->proxy_negotiate_state :
                                    &conn->http_negotiate_state;
#endif
  unsigned long *availp;
  struct auth *authp;

  if(proxy) {
    availp = &data->info.proxyauthavail;
    authp = &data->state.authproxy;
  }
  else {
    availp = &data->info.httpauthavail;
    authp = &data->state.authhost;
  }

  /*
   * Here we check if we want the specific single authentication (using ==) and
   * if we do, we initiate usage of it.
   *
   * If the provided authentication is wanted as one out of several accepted
   * types (using &), we OR this authentication type to the authavail
   * variable.
   *
   * Note:
   *
   * ->picked is first set to the 'want' value (one or more bits) before the
   * request is sent, and then it is again set _after_ all response 401/407
   * headers have been received but then only to a single preferred method
   * (bit).
   */

  while(*auth) {
#ifdef USE_SPNEGO
    if(checkprefix("Negotiate", auth)) {
      if((authp->avail & CURLAUTH_NEGOTIATE) ||
         Curl_auth_is_spnego_supported()) {
        *availp |= CURLAUTH_NEGOTIATE;
        authp->avail |= CURLAUTH_NEGOTIATE;

        if(authp->picked == CURLAUTH_NEGOTIATE) {
          CURLcode result = Curl_input_negotiate(conn, proxy, auth);
          if(!result) {
            DEBUGASSERT(!data->req.newurl);
            data->req.newurl = strdup(data->change.url);
            if(!data->req.newurl)
              return CURLE_OUT_OF_MEMORY;
            data->state.authproblem = FALSE;
            /* we received a GSS auth token and we dealt with it fine */
            *negstate = GSS_AUTHRECV;
          }
          else
            data->state.authproblem = TRUE;
        }
      }
    }
    else
#endif
#ifdef USE_NTLM
      /* NTLM support requires the SSL crypto libs */
      if(checkprefix("NTLM", auth)) {
        if((authp->avail & CURLAUTH_NTLM) ||
           (authp->avail & CURLAUTH_NTLM_WB) ||
           Curl_auth_is_ntlm_supported()) {
          *availp |= CURLAUTH_NTLM;
          authp->avail |= CURLAUTH_NTLM;

          if(authp->picked == CURLAUTH_NTLM ||
             authp->picked == CURLAUTH_NTLM_WB) {
            /* NTLM authentication is picked and activated */
            CURLcode result = Curl_input_ntlm(conn, proxy, auth);
            if(!result) {
              data->state.authproblem = FALSE;
#ifdef NTLM_WB_ENABLED
              if(authp->picked == CURLAUTH_NTLM_WB) {
                *availp &= ~CURLAUTH_NTLM;
                authp->avail &= ~CURLAUTH_NTLM;
                *availp |= CURLAUTH_NTLM_WB;
                authp->avail |= CURLAUTH_NTLM_WB;

                result = Curl_input_ntlm_wb(conn, proxy, auth);
                if(result) {
                  infof(data, "Authentication problem. Ignoring this.\n");
                  data->state.authproblem = TRUE;
                }
              }
#endif
            }
            else {
              infof(data, "Authentication problem. Ignoring this.\n");
              data->state.authproblem = TRUE;
            }
          }
        }
      }
      else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
        if(checkprefix("Digest", auth)) {
          if((authp->avail & CURLAUTH_DIGEST) != 0)
            infof(data, "Ignoring duplicate digest auth header.\n");
          else if(Curl_auth_is_digest_supported()) {
            CURLcode result;

            *availp |= CURLAUTH_DIGEST;
            authp->avail |= CURLAUTH_DIGEST;

            /* We call this function on input Digest headers even if Digest
             * authentication isn't activated yet, as we need to store the
             * incoming data from this header in case we are going to use
             * Digest */
            result = Curl_input_digest(conn, proxy, auth);
            if(result) {
              infof(data, "Authentication problem. Ignoring this.\n");
              data->state.authproblem = TRUE;
            }
          }
        }
        else
#endif
          if(checkprefix("Basic", auth)) {
            *availp |= CURLAUTH_BASIC;
            authp->avail |= CURLAUTH_BASIC;
            if(authp->picked == CURLAUTH_BASIC) {
              /* We asked for Basic authentication but got a 40X back
                 anyway, which basically means our name+password isn't
                 valid. */
              authp->avail = CURLAUTH_NONE;
              infof(data, "Authentication problem. Ignoring this.\n");
              data->state.authproblem = TRUE;
            }
          }
          else
            if(checkprefix("Bearer", auth)) {
              *availp |= CURLAUTH_BEARER;
              authp->avail |= CURLAUTH_BEARER;
              if(authp->picked == CURLAUTH_BEARER) {
                /* We asked for Bearer authentication but got a 40X back
                  anyway, which basically means our token isn't valid. */
                authp->avail = CURLAUTH_NONE;
                infof(data, "Authentication problem. Ignoring this.\n");
                data->state.authproblem = TRUE;
              }
            }

    /* there may be multiple methods on one line, so keep reading */
    while(*auth && *auth != ',') /* read up to the next comma */
      auth++;
    if(*auth == ',') /* if we're on a comma, skip it */
      auth++;
    while(*auth && ISSPACE(*auth))
      auth++;
  }

  return CURLE_OK;
}