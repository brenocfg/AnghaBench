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
struct httprequest {char* reqbuf; int checkindex; size_t offset; int cl; void* pipelining; scalar_t__ pipe; scalar_t__ skip; scalar_t__ rtp_buffersize; int /*<<< orphan*/ * rtp_buffer; scalar_t__ prot_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  rcmd; void* ntlm; void* digest; void* auth; void* auth_req; int /*<<< orphan*/  open; scalar_t__ partno; int /*<<< orphan*/  testno; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOCNUMBER_NOTHING ; 
 void* FALSE ; 
 int ProcessRequest (struct httprequest*) ; 
 int /*<<< orphan*/  RCMD_NORMALREQ ; 
 int REQBUFSIZ ; 
 int /*<<< orphan*/  RPROT_NONE ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ curlx_uztosz (size_t) ; 
 scalar_t__ got_exit_signal ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 scalar_t__ sread (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  storerequest (char*,size_t) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int get_request(curl_socket_t sock, struct httprequest *req)
{
  int error;
  int fail = 0;
  int done_processing = 0;
  char *reqbuf = req->reqbuf;
  ssize_t got = 0;

  char *pipereq = NULL;
  size_t pipereq_length = 0;

  if(req->pipelining) {
    pipereq = reqbuf + req->checkindex;
    pipereq_length = req->offset - req->checkindex;
  }

  /*** Init the httprequest structure properly for the upcoming request ***/

  req->checkindex = 0;
  req->offset = 0;
  req->testno = DOCNUMBER_NOTHING;
  req->partno = 0;
  req->open = TRUE;
  req->auth_req = FALSE;
  req->auth = FALSE;
  req->cl = 0;
  req->digest = FALSE;
  req->ntlm = FALSE;
  req->pipe = 0;
  req->skip = 0;
  req->rcmd = RCMD_NORMALREQ;
  req->protocol = RPROT_NONE;
  req->prot_version = 0;
  req->pipelining = FALSE;
  req->rtp_buffer = NULL;
  req->rtp_buffersize = 0;

  /*** end of httprequest init ***/

  while(!done_processing && (req->offset < REQBUFSIZ-1)) {
    if(pipereq_length && pipereq) {
      memmove(reqbuf, pipereq, pipereq_length);
      got = curlx_uztosz(pipereq_length);
      pipereq_length = 0;
    }
    else {
      if(req->skip)
        /* we are instructed to not read the entire thing, so we make sure to
           only read what we're supposed to and NOT read the enire thing the
           client wants to send! */
        got = sread(sock, reqbuf + req->offset, req->cl);
      else
        got = sread(sock, reqbuf + req->offset, REQBUFSIZ-1 - req->offset);
    }
    if(got_exit_signal)
      return 1;
    if(got == 0) {
      logmsg("Connection closed by client");
      fail = 1;
    }
    else if(got < 0) {
      error = SOCKERRNO;
      logmsg("recv() returned error: (%d) %s", error, strerror(error));
      fail = 1;
    }
    if(fail) {
      /* dump the request received so far to the external file */
      reqbuf[req->offset] = '\0';
      storerequest(reqbuf, req->offset);
      return 1;
    }

    logmsg("Read %zd bytes", got);

    req->offset += (size_t)got;
    reqbuf[req->offset] = '\0';

    done_processing = ProcessRequest(req);
    if(got_exit_signal)
      return 1;
    if(done_processing && req->pipe) {
      logmsg("Waiting for another piped request");
      done_processing = 0;
      req->pipe--;
    }
  }

  if((req->offset == REQBUFSIZ-1) && (got > 0)) {
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

  /* dump the request to an external file */
  storerequest(reqbuf, req->pipelining ? req->checkindex : req->offset);
  if(got_exit_signal)
    return 1;

  return fail; /* return 0 on success */
}