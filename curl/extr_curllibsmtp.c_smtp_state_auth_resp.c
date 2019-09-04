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
struct smtp_conn {int /*<<< orphan*/  sasl; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  smtpstate ;
typedef  int saslprogress ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_LOGIN_DENIED ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_sasl_continue (int /*<<< orphan*/ *,struct connectdata*,int,int*) ; 
#define  SASL_DONE 129 
#define  SASL_IDLE 128 
 int /*<<< orphan*/  SMTP_STOP ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_state_auth_resp(struct connectdata *conn,
                                     int smtpcode,
                                     smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  saslprogress progress;

  (void)instate; /* no use for this yet */

  result = Curl_sasl_continue(&smtpc->sasl, conn, smtpcode, &progress);
  if(!result)
    switch(progress) {
    case SASL_DONE:
      state(conn, SMTP_STOP);  /* Authenticated */
      break;
    case SASL_IDLE:            /* No mechanism left after cancellation */
      failf(data, "Authentication cancelled");
      result = CURLE_LOGIN_DENIED;
      break;
    default:
      break;
    }

  return result;
}