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
struct pop3_conn {int /*<<< orphan*/  apoptimestamp; TYPE_1__ sasl; TYPE_5__ pp; } ;
struct TYPE_7__ {struct pop3_conn pop3c; } ;
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
 int /*<<< orphan*/  pop3_block_statemach (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop3_perform_quit (struct connectdata*) ; 

__attribute__((used)) static CURLcode pop3_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to. */

  /* The POP3 session may or may not have been allocated/setup at this
     point! */
  if(!dead_connection && pop3c->pp.conn && pop3c->pp.conn->bits.protoconnstart)
    if(!pop3_perform_quit(conn))
      (void)pop3_block_statemach(conn, TRUE); /* ignore errors on QUIT */

  /* Disconnect from the server */
  Curl_pp_disconnect(&pop3c->pp);

  /* Cleanup the SASL module */
  Curl_sasl_cleanup(conn, pop3c->sasl.authused);

  /* Cleanup our connection based variables */
  Curl_safefree(pop3c->apoptimestamp);

  return CURLE_OK;
}