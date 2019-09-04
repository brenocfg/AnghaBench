#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* authused; void* authmechs; } ;
struct pop3_conn {int /*<<< orphan*/  pp; int /*<<< orphan*/  tls_supported; TYPE_2__ sasl; } ;
struct TYPE_3__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  POP3_CAPA ; 
 void* SASL_AUTH_NONE ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_perform_capa(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  pop3c->sasl.authmechs = SASL_AUTH_NONE; /* No known auth. mechanisms yet */
  pop3c->sasl.authused = SASL_AUTH_NONE;  /* Clear the auth. mechanism used */
  pop3c->tls_supported = FALSE;           /* Clear the TLS capability */

  /* Send the CAPA command */
  result = Curl_pp_sendf(&pop3c->pp, "%s", "CAPA");

  if(!result)
    state(conn, POP3_CAPA);

  return result;
}