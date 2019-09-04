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
struct imap_conn {int preftype; int /*<<< orphan*/  login_disabled; int /*<<< orphan*/  ir_supported; int /*<<< orphan*/  sasl; scalar_t__ preauth; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;
typedef  scalar_t__ saslprogress ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_LOGIN_DENIED ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_sasl_can_authenticate (int /*<<< orphan*/ *,struct connectdata*) ; 
 scalar_t__ Curl_sasl_start (int /*<<< orphan*/ *,struct connectdata*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IMAP_AUTHENTICATE ; 
 int /*<<< orphan*/  IMAP_STOP ; 
 int IMAP_TYPE_CLEARTEXT ; 
 scalar_t__ SASL_INPROGRESS ; 
 scalar_t__ imap_perform_login (struct connectdata*) ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;
  saslprogress progress;

  /* Check if already authenticated OR if there is enough data to authenticate
     with and end the connect phase if we don't */
  if(imapc->preauth ||
     !Curl_sasl_can_authenticate(&imapc->sasl, conn)) {
    state(conn, IMAP_STOP);
    return result;
  }

  /* Calculate the SASL login details */
  result = Curl_sasl_start(&imapc->sasl, conn, imapc->ir_supported, &progress);

  if(!result) {
    if(progress == SASL_INPROGRESS)
      state(conn, IMAP_AUTHENTICATE);
    else if(!imapc->login_disabled && (imapc->preftype & IMAP_TYPE_CLEARTEXT))
      /* Perform clear text authentication */
      result = imap_perform_login(conn);
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}