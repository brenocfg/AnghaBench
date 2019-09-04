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
struct smtp_conn {int /*<<< orphan*/  sasl; int /*<<< orphan*/  auth_supported; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;
typedef  scalar_t__ saslprogress ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_LOGIN_DENIED ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_sasl_can_authenticate (int /*<<< orphan*/ *,struct connectdata*) ; 
 scalar_t__ Curl_sasl_start (int /*<<< orphan*/ *,struct connectdata*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SASL_INPROGRESS ; 
 int /*<<< orphan*/  SMTP_AUTH ; 
 int /*<<< orphan*/  SMTP_STOP ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  saslprogress progress;

  /* Check we have enough data to authenticate with, and the
     server supports authentiation, and end the connect phase if not */
  if(!smtpc->auth_supported ||
     !Curl_sasl_can_authenticate(&smtpc->sasl, conn)) {
    state(conn, SMTP_STOP);
    return result;
  }

  /* Calculate the SASL login details */
  result = Curl_sasl_start(&smtpc->sasl, conn, FALSE, &progress);

  if(!result) {
    if(progress == SASL_INPROGRESS)
      state(conn, SMTP_AUTH);
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}