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
struct imap_conn {int /*<<< orphan*/  tls_supported; TYPE_2__ sasl; } ;
struct TYPE_3__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMAP_CAPABILITY ; 
 void* SASL_AUTH_NONE ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_capability(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;
  imapc->sasl.authmechs = SASL_AUTH_NONE; /* No known auth. mechanisms yet */
  imapc->sasl.authused = SASL_AUTH_NONE;  /* Clear the auth. mechanism used */
  imapc->tls_supported = FALSE;           /* Clear the TLS capability */

  /* Send the CAPABILITY command */
  result = imap_sendf(conn, "CAPABILITY");

  if(!result)
    state(conn, IMAP_CAPABILITY);

  return result;
}