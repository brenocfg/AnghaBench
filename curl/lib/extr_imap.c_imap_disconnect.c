#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  authused; } ;
struct TYPE_10__ {TYPE_4__* conn; } ;
struct imap_conn {int /*<<< orphan*/  mailbox_uidvalidity; int /*<<< orphan*/  mailbox; TYPE_1__ sasl; TYPE_5__ pp; } ;
struct TYPE_7__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_2__ proto; } ;
struct TYPE_8__ {scalar_t__ protoconnstart; } ;
struct TYPE_9__ {TYPE_3__ bits; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_disconnect (TYPE_5__*) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_sasl_cleanup (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  imap_block_statemach (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imap_perform_logout (struct connectdata*) ; 

__attribute__((used)) static CURLcode imap_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct imap_conn *imapc = &conn->proto.imapc;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to. */

  /* The IMAP session may or may not have been allocated/setup at this
     point! */
  if(!dead_connection && imapc->pp.conn && imapc->pp.conn->bits.protoconnstart)
    if(!imap_perform_logout(conn))
      (void)imap_block_statemach(conn, TRUE); /* ignore errors on LOGOUT */

  /* Disconnect from the server */
  Curl_pp_disconnect(&imapc->pp);

  /* Cleanup the SASL module */
  Curl_sasl_cleanup(conn, imapc->sasl.authused);

  /* Cleanup our connection based variables */
  Curl_safefree(imapc->mailbox);
  Curl_safefree(imapc->mailbox_uidvalidity);

  return CURLE_OK;
}