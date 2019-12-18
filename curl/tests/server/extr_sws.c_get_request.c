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
struct httprequest {char* reqbuf; int offset; int cl; scalar_t__ done_processing; scalar_t__ skip; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EWOULDBLOCK ; 
 scalar_t__ ProcessRequest (struct httprequest*) ; 
 int REQBUFSIZ ; 
 int SOCKERRNO ; 
 scalar_t__ got_exit_signal ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 scalar_t__ sread (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  storerequest (char*,size_t) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int get_request(curl_socket_t sock, struct httprequest *req)
{
  int fail = 0;
  char *reqbuf = req->reqbuf;
  ssize_t got = 0;
  int overflow = 0;

  if(req->offset >= REQBUFSIZ-1) {
    /* buffer is already full; do nothing */
    overflow = 1;
  }
  else {
    if(req->skip)
      /* we are instructed to not read the entire thing, so we make sure to
         only read what we're supposed to and NOT read the enire thing the
         client wants to send! */
      got = sread(sock, reqbuf + req->offset, req->cl);
    else
      got = sread(sock, reqbuf + req->offset, REQBUFSIZ-1 - req->offset);

    if(got_exit_signal)
      return -1;
    if(got == 0) {
      logmsg("Connection closed by client");
      fail = 1;
    }
    else if(got < 0) {
      int error = SOCKERRNO;
      if(EAGAIN == error || EWOULDBLOCK == error) {
        /* nothing to read at the moment */
        return 0;
      }
      logmsg("recv() returned error: (%d) %s", error, strerror(error));
      fail = 1;
    }
    if(fail) {
      /* dump the request received so far to the external file */
      reqbuf[req->offset] = '\0';
      storerequest(reqbuf, req->offset);
      return -1;
    }

    logmsg("Read %zd bytes", got);

    req->offset += (size_t)got;
    reqbuf[req->offset] = '\0';

    req->done_processing = ProcessRequest(req);
    if(got_exit_signal)
      return -1;
  }

  if(overflow || (req->offset == REQBUFSIZ-1 && got > 0)) {
    logmsg("Request would overflow buffer, closing connection");
    /* dump request received so far to external file anyway */
    reqbuf[REQBUFSIZ-1] = '\0';
    fail = 1;
  }
  else if(req->offset > REQBUFSIZ-1) {
    logmsg("Request buffer overflow, closing connection");
    /* dump request received so far to external file anyway */
    reqbuf[REQBUFSIZ-1] = '\0';
    fail = 1;
  }
  else
    reqbuf[req->offset] = '\0';

  /* at the end of a request dump it to an external file */
  if(fail || req->done_processing)
    storerequest(reqbuf, req->offset);
  if(got_exit_signal)
    return -1;

  return fail ? -1 : 1;
}