#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pop3_conn {int authtypes; int preftype; int /*<<< orphan*/  sasl; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct Curl_easy {int dummy; } ;
typedef  int saslprogress ;
typedef  int /*<<< orphan*/  pop3state ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_LOGIN_DENIED ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_sasl_continue (int /*<<< orphan*/ *,struct connectdata*,int,int*) ; 
 int /*<<< orphan*/  POP3_STOP ; 
 int POP3_TYPE_APOP ; 
 int POP3_TYPE_CLEARTEXT ; 
#define  SASL_DONE 129 
#define  SASL_IDLE 128 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  pop3_perform_apop (struct connectdata*) ; 
 int /*<<< orphan*/  pop3_perform_user (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_state_auth_resp(struct connectdata *conn,
                                     int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  saslprogress progress;

  (void)instate; /* no use for this yet */

  result = Curl_sasl_continue(&pop3c->sasl, conn, pop3code, &progress);
  if(!result)
    switch(progress) {
    case SASL_DONE:
      state(conn, POP3_STOP);  /* Authenticated */
      break;
    case SASL_IDLE:            /* No mechanism left after cancellation */
#ifndef CURL_DISABLE_CRYPTO_AUTH
      if(pop3c->authtypes & pop3c->preftype & POP3_TYPE_APOP)
        /* Perform APOP authentication */
        result = pop3_perform_apop(conn);
      else
#endif
      if(pop3c->authtypes & pop3c->preftype & POP3_TYPE_CLEARTEXT)
        /* Perform clear text authentication */
        result = pop3_perform_user(conn);
      else {
        failf(data, "Authentication cancelled");
        result = CURLE_LOGIN_DENIED;
      }
      break;
    default:
      break;
    }

  return result;
}