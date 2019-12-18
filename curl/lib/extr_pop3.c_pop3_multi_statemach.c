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
struct pop3_conn {scalar_t__ state; int /*<<< orphan*/  pp; int /*<<< orphan*/  ssldone; } ;
struct TYPE_3__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_2__* handler; TYPE_1__ proto; } ;
struct TYPE_4__ {int flags; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_statemach (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ Curl_ssl_connect_nonblocking (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 scalar_t__ POP3_STOP ; 
 int PROTOPT_SSL ; 
 int TRUE ; 

__attribute__((used)) static CURLcode pop3_multi_statemach(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  if((conn->handler->flags & PROTOPT_SSL) && !pop3c->ssldone) {
    result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &pop3c->ssldone);
    if(result || !pop3c->ssldone)
      return result;
  }

  result = Curl_pp_statemach(&pop3c->pp, FALSE, FALSE);
  *done = (pop3c->state == POP3_STOP) ? TRUE : FALSE;

  return result;
}