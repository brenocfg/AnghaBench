#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int time_t ;
struct pingpong {scalar_t__ (* statemach_act ) (struct connectdata*) ;scalar_t__ sendleft; struct connectdata* conn; } ;
struct connectdata {struct Curl_easy* data; int /*<<< orphan*/ * sock; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_ABORTED_BY_CALLBACK ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OPERATION_TIMEDOUT ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_now () ; 
 scalar_t__ Curl_pgrsUpdate (struct connectdata*) ; 
 scalar_t__ Curl_pp_moredata (struct pingpong*) ; 
 int Curl_pp_state_timeout (struct pingpong*,int) ; 
 int Curl_socket_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ Curl_speedcheck (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_ssl_data_pending (struct connectdata*,size_t) ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 scalar_t__ stub1 (struct connectdata*) ; 

CURLcode Curl_pp_statemach(struct pingpong *pp, bool block,
                           bool disconnecting)
{
  struct connectdata *conn = pp->conn;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int rc;
  time_t interval_ms;
  time_t timeout_ms = Curl_pp_state_timeout(pp, disconnecting);
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;

  if(timeout_ms <= 0) {
    failf(data, "server response timeout");
    return CURLE_OPERATION_TIMEDOUT; /* already too little time */
  }

  if(block) {
    interval_ms = 1000;  /* use 1 second timeout intervals */
    if(timeout_ms < interval_ms)
      interval_ms = timeout_ms;
  }
  else
    interval_ms = 0; /* immediate */

  if(Curl_ssl_data_pending(conn, FIRSTSOCKET))
    rc = 1;
  else if(Curl_pp_moredata(pp))
    /* We are receiving and there is data in the cache so just read it */
    rc = 1;
  else if(!pp->sendleft && Curl_ssl_data_pending(conn, FIRSTSOCKET))
    /* We are receiving and there is data ready in the SSL library */
    rc = 1;
  else
    rc = Curl_socket_check(pp->sendleft?CURL_SOCKET_BAD:sock, /* reading */
                           CURL_SOCKET_BAD,
                           pp->sendleft?sock:CURL_SOCKET_BAD, /* writing */
                           interval_ms);

  if(block) {
    /* if we didn't wait, we don't have to spend time on this now */
    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else
      result = Curl_speedcheck(data, Curl_now());

    if(result)
      return result;
  }

  if(rc == -1) {
    failf(data, "select/poll error");
    result = CURLE_OUT_OF_MEMORY;
  }
  else if(rc)
    result = pp->statemach_act(conn);

  return result;
}