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
struct httprequest {int testno; int partno; scalar_t__ open; scalar_t__ upgrade_request; int /*<<< orphan*/  connect_port; scalar_t__ connect_request; int /*<<< orphan*/  done_processing; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int get_request (int /*<<< orphan*/ ,struct httprequest*) ; 
 scalar_t__ got_exit_signal ; 
 int /*<<< orphan*/  http2 (struct httprequest*) ; 
 int /*<<< orphan*/  http_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_proxy ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 scalar_t__ prevbounce ; 
 int prevpartno ; 
 int prevtestno ; 
 int /*<<< orphan*/  send_doc (int /*<<< orphan*/ ,struct httprequest*) ; 

__attribute__((used)) static int service_connection(curl_socket_t msgsock, struct httprequest *req,
                              curl_socket_t listensock,
                              const char *connecthost)
{
  if(got_exit_signal)
    return -1;

  while(!req->done_processing) {
    int rc = get_request(msgsock, req);
    if(rc <= 0) {
      /* Nothing further to read now, possibly because the socket was closed */
      return rc;
    }
  }

  if(prevbounce) {
    /* bounce treatment requested */
    if((req->testno == prevtestno) &&
       (req->partno == prevpartno)) {
      req->partno++;
      logmsg("BOUNCE part number to %ld", req->partno);
    }
    else {
      prevbounce = FALSE;
      prevtestno = -1;
      prevpartno = -1;
    }
  }

  send_doc(msgsock, req);
  if(got_exit_signal)
    return -1;

  if(req->testno < 0) {
    logmsg("special request received, no persistency");
    return -1;
  }
  if(!req->open) {
    logmsg("instructed to close connection after server-reply");
    return -1;
  }

  if(req->connect_request) {
    /* a CONNECT request, setup and talk the tunnel */
    if(!is_proxy) {
      logmsg("received CONNECT but isn't running as proxy!");
      return 1;
    }
    else {
      http_connect(&msgsock, listensock, connecthost, req->connect_port);
      return -1;
    }
  }

  if(req->upgrade_request) {
    /* an upgrade request, switch to http2 here */
    http2(req);
    return -1;
  }

  /* if we got a CONNECT, loop and get another request as well! */

  if(req->open) {
    logmsg("=> persistent connection request ended, awaits new request\n");
    return 1;
  }

  return -1;
}