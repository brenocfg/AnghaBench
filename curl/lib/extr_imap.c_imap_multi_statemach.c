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
struct imap_conn {scalar_t__ state; int /*<<< orphan*/  pp; int /*<<< orphan*/  ssldone; } ;
struct TYPE_3__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_2__* handler; TYPE_1__ proto; } ;
struct TYPE_4__ {int flags; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_statemach (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ Curl_ssl_connect_nonblocking (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 scalar_t__ IMAP_STOP ; 
 int PROTOPT_SSL ; 
 int TRUE ; 

__attribute__((used)) static CURLcode imap_multi_statemach(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;

  if((conn->handler->flags & PROTOPT_SSL) && !imapc->ssldone) {
    result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &imapc->ssldone);
    if(result || !imapc->ssldone)
      return result;
  }

  result = Curl_pp_statemach(&imapc->pp, FALSE, FALSE);
  *done = (imapc->state == IMAP_STOP) ? TRUE : FALSE;

  return result;
}