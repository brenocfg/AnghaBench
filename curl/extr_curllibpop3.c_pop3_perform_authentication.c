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
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;
typedef  scalar_t__ saslprogress ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_LOGIN_DENIED ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_sasl_can_authenticate (int /*<<< orphan*/ *,struct connectdata*) ; 
 scalar_t__ Curl_sasl_start (int /*<<< orphan*/ *,struct connectdata*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  POP3_AUTH ; 
 int /*<<< orphan*/  POP3_STOP ; 
 int POP3_TYPE_APOP ; 
 int POP3_TYPE_CLEARTEXT ; 
 int POP3_TYPE_SASL ; 
 scalar_t__ SASL_IDLE ; 
 scalar_t__ SASL_INPROGRESS ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pop3_perform_apop (struct connectdata*) ; 
 scalar_t__ pop3_perform_user (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  saslprogress progress = SASL_IDLE;

  /* Check we have enough data to authenticate with and end the
     connect phase if we don't */
  if(!Curl_sasl_can_authenticate(&pop3c->sasl, conn)) {
    state(conn, POP3_STOP);
    return result;
  }

  if(pop3c->authtypes & pop3c->preftype & POP3_TYPE_SASL) {
    /* Calculate the SASL login details */
    result = Curl_sasl_start(&pop3c->sasl, conn, FALSE, &progress);

    if(!result)
      if(progress == SASL_INPROGRESS)
        state(conn, POP3_AUTH);
  }

  if(!result && progress == SASL_IDLE) {
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
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}