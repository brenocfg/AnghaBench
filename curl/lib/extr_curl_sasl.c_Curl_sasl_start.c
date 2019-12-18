#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ user_passwd; } ;
struct TYPE_11__ {char* name; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_10__ {TYPE_1__ host; } ;
struct connectdata {long port; long remote_port; int /*<<< orphan*/  user; int /*<<< orphan*/ * passwd; int /*<<< orphan*/  sasl_authzid; int /*<<< orphan*/  oauth_bearer; int /*<<< orphan*/  ntlm; int /*<<< orphan*/  krb5; TYPE_5__ bits; TYPE_3__ host; TYPE_2__ http_proxy; struct Curl_easy* data; } ;
struct SASL {int force_ir; unsigned int authused; unsigned int authmechs; unsigned int prefmech; TYPE_4__* params; int /*<<< orphan*/  mutual_auth; } ;
struct TYPE_16__ {char** str; scalar_t__ sasl_ir; } ;
struct Curl_easy {TYPE_8__ set; TYPE_7__* conn; } ;
typedef  int /*<<< orphan*/  saslstate ;
typedef  int /*<<< orphan*/  saslprogress ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {TYPE_6__ host; } ;
struct TYPE_12__ {char* service; scalar_t__ maxirlen; scalar_t__ (* sendauth ) (struct connectdata*,char const*,char*) ;} ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_auth_create_external_message (struct Curl_easy*,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ Curl_auth_create_gssapi_user_message (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,size_t*) ; 
 scalar_t__ Curl_auth_create_login_message (struct Curl_easy*,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ Curl_auth_create_ntlm_type1_message (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const* const,int /*<<< orphan*/ *,char**,size_t*) ; 
 scalar_t__ Curl_auth_create_oauth_bearer_message (struct Curl_easy*,int /*<<< orphan*/ ,char const* const,long const,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ Curl_auth_create_plain_message (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,size_t*) ; 
 scalar_t__ Curl_auth_create_xoauth_bearer_message (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ Curl_auth_is_digest_supported () ; 
 scalar_t__ Curl_auth_is_gssapi_supported () ; 
 scalar_t__ Curl_auth_is_ntlm_supported () ; 
 scalar_t__ Curl_auth_user_contains_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SASL_CRAMMD5 ; 
 int /*<<< orphan*/  SASL_DIGESTMD5 ; 
 int /*<<< orphan*/  SASL_EXTERNAL ; 
 int /*<<< orphan*/  SASL_FINAL ; 
 int /*<<< orphan*/  SASL_GSSAPI ; 
 int /*<<< orphan*/  SASL_GSSAPI_TOKEN ; 
 int /*<<< orphan*/  SASL_IDLE ; 
 int /*<<< orphan*/  SASL_INPROGRESS ; 
 int /*<<< orphan*/  SASL_LOGIN ; 
 int /*<<< orphan*/  SASL_LOGIN_PASSWD ; 
 unsigned int SASL_MECH_CRAM_MD5 ; 
 unsigned int SASL_MECH_DIGEST_MD5 ; 
 unsigned int SASL_MECH_EXTERNAL ; 
 unsigned int SASL_MECH_GSSAPI ; 
 unsigned int SASL_MECH_LOGIN ; 
 unsigned int SASL_MECH_NTLM ; 
 unsigned int SASL_MECH_OAUTHBEARER ; 
 unsigned int SASL_MECH_PLAIN ; 
 char* SASL_MECH_STRING_CRAM_MD5 ; 
 char* SASL_MECH_STRING_DIGEST_MD5 ; 
 char* SASL_MECH_STRING_EXTERNAL ; 
 char* SASL_MECH_STRING_GSSAPI ; 
 char* SASL_MECH_STRING_LOGIN ; 
 char* SASL_MECH_STRING_NTLM ; 
 char* SASL_MECH_STRING_OAUTHBEARER ; 
 char* SASL_MECH_STRING_PLAIN ; 
 char* SASL_MECH_STRING_XOAUTH2 ; 
 unsigned int SASL_MECH_XOAUTH2 ; 
 int /*<<< orphan*/  SASL_NTLM ; 
 int /*<<< orphan*/  SASL_NTLM_TYPE2MSG ; 
 int /*<<< orphan*/  SASL_OAUTH2 ; 
 int /*<<< orphan*/  SASL_OAUTH2_RESP ; 
 int /*<<< orphan*/  SASL_PLAIN ; 
 int /*<<< orphan*/  SASL_STOP ; 
 scalar_t__ SSL_IS_PROXY () ; 
 size_t STRING_SERVICE_NAME ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  state (struct SASL*,struct connectdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ stub1 (struct connectdata*,char const*,char*) ; 

CURLcode Curl_sasl_start(struct SASL *sasl, struct connectdata *conn,
                         bool force_ir, saslprogress *progress)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  unsigned int enabledmechs;
  const char *mech = NULL;
  char *resp = NULL;
  size_t len = 0;
  saslstate state1 = SASL_STOP;
  saslstate state2 = SASL_FINAL;
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
  const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
#if defined(USE_KERBEROS5) || defined(USE_NTLM)
  const char *service = data->set.str[STRING_SERVICE_NAME] ?
    data->set.str[STRING_SERVICE_NAME] :
    sasl->params->service;
#endif

  sasl->force_ir = force_ir;    /* Latch for future use */
  sasl->authused = 0;           /* No mechanism used yet */
  enabledmechs = sasl->authmechs & sasl->prefmech;
  *progress = SASL_IDLE;

  /* Calculate the supported authentication mechanism, by decreasing order of
     security, as well as the initial response where appropriate */
  if((enabledmechs & SASL_MECH_EXTERNAL) && !conn->passwd[0]) {
    mech = SASL_MECH_STRING_EXTERNAL;
    state1 = SASL_EXTERNAL;
    sasl->authused = SASL_MECH_EXTERNAL;

    if(force_ir || data->set.sasl_ir)
      result = Curl_auth_create_external_message(data, conn->user, &resp,
                                                 &len);
  }
  else if(conn->bits.user_passwd) {
#if defined(USE_KERBEROS5)
    if((enabledmechs & SASL_MECH_GSSAPI) && Curl_auth_is_gssapi_supported() &&
       Curl_auth_user_contains_domain(conn->user)) {
      sasl->mutual_auth = FALSE;
      mech = SASL_MECH_STRING_GSSAPI;
      state1 = SASL_GSSAPI;
      state2 = SASL_GSSAPI_TOKEN;
      sasl->authused = SASL_MECH_GSSAPI;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_gssapi_user_message(data, conn->user,
                                                      conn->passwd,
                                                      service,
                                                      data->conn->host.name,
                                                      sasl->mutual_auth,
                                                      NULL, &conn->krb5,
                                                      &resp, &len);
    }
    else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
    if((enabledmechs & SASL_MECH_DIGEST_MD5) &&
       Curl_auth_is_digest_supported()) {
      mech = SASL_MECH_STRING_DIGEST_MD5;
      state1 = SASL_DIGESTMD5;
      sasl->authused = SASL_MECH_DIGEST_MD5;
    }
    else if(enabledmechs & SASL_MECH_CRAM_MD5) {
      mech = SASL_MECH_STRING_CRAM_MD5;
      state1 = SASL_CRAMMD5;
      sasl->authused = SASL_MECH_CRAM_MD5;
    }
    else
#endif
#ifdef USE_NTLM
    if((enabledmechs & SASL_MECH_NTLM) && Curl_auth_is_ntlm_supported()) {
      mech = SASL_MECH_STRING_NTLM;
      state1 = SASL_NTLM;
      state2 = SASL_NTLM_TYPE2MSG;
      sasl->authused = SASL_MECH_NTLM;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_ntlm_type1_message(data,
                                                     conn->user, conn->passwd,
                                                     service,
                                                     hostname,
                                                     &conn->ntlm, &resp,
                                                     &len);
      }
    else
#endif
    if((enabledmechs & SASL_MECH_OAUTHBEARER) && conn->oauth_bearer) {
      mech = SASL_MECH_STRING_OAUTHBEARER;
      state1 = SASL_OAUTH2;
      state2 = SASL_OAUTH2_RESP;
      sasl->authused = SASL_MECH_OAUTHBEARER;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_oauth_bearer_message(data, conn->user,
                                                       hostname,
                                                       port,
                                                       conn->oauth_bearer,
                                                       &resp, &len);
    }
    else if((enabledmechs & SASL_MECH_XOAUTH2) && conn->oauth_bearer) {
      mech = SASL_MECH_STRING_XOAUTH2;
      state1 = SASL_OAUTH2;
      sasl->authused = SASL_MECH_XOAUTH2;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_xoauth_bearer_message(data, conn->user,
                                                        conn->oauth_bearer,
                                                        &resp, &len);
    }
    else if(enabledmechs & SASL_MECH_PLAIN) {
      mech = SASL_MECH_STRING_PLAIN;
      state1 = SASL_PLAIN;
      sasl->authused = SASL_MECH_PLAIN;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_plain_message(data, conn->sasl_authzid,
                                                conn->user, conn->passwd,
                                                &resp, &len);
    }
    else if(enabledmechs & SASL_MECH_LOGIN) {
      mech = SASL_MECH_STRING_LOGIN;
      state1 = SASL_LOGIN;
      state2 = SASL_LOGIN_PASSWD;
      sasl->authused = SASL_MECH_LOGIN;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_login_message(data, conn->user, &resp, &len);
    }
  }

  if(!result && mech) {
    if(resp && sasl->params->maxirlen &&
       strlen(mech) + len > sasl->params->maxirlen) {
      free(resp);
      resp = NULL;
    }

    result = sasl->params->sendauth(conn, mech, resp);
    if(!result) {
      *progress = SASL_INPROGRESS;
      state(sasl, conn, resp ? state2 : state1);
    }
  }

  free(resp);

  return result;
}