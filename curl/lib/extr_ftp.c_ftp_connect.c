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
struct pingpong {struct connectdata* conn; int /*<<< orphan*/  endofresp; int /*<<< orphan*/  statemach_act; int /*<<< orphan*/  response_time; } ;
struct ftp_conn {struct pingpong pp; } ;
struct TYPE_4__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__* handler; TYPE_2__ proto; } ;
struct TYPE_3__ {int flags; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_pp_init (struct pingpong*) ; 
 scalar_t__ Curl_ssl_connect (struct connectdata*,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 int /*<<< orphan*/  FTP_WAIT220 ; 
 int PROTOPT_SSL ; 
 int /*<<< orphan*/  RESP_TIMEOUT ; 
 int /*<<< orphan*/  connkeep (struct connectdata*,char*) ; 
 int /*<<< orphan*/  ftp_endofresp ; 
 scalar_t__ ftp_multi_statemach (struct connectdata*,int*) ; 
 int /*<<< orphan*/  ftp_statemach_act ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_connect(struct connectdata *conn,
                                 bool *done) /* see description above */
{
  CURLcode result;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct pingpong *pp = &ftpc->pp;

  *done = FALSE; /* default to not done yet */

  /* We always support persistent connections on ftp */
  connkeep(conn, "FTP default");

  pp->response_time = RESP_TIMEOUT; /* set default response time-out */
  pp->statemach_act = ftp_statemach_act;
  pp->endofresp = ftp_endofresp;
  pp->conn = conn;

  if(conn->handler->flags & PROTOPT_SSL) {
    /* BLOCKING */
    result = Curl_ssl_connect(conn, FIRSTSOCKET);
    if(result)
      return result;
  }

  Curl_pp_init(pp); /* init the generic pingpong data */

  /* When we connect, we start in the state where we await the 220
     response */
  state(conn, FTP_WAIT220);

  result = ftp_multi_statemach(conn, done);

  return result;
}