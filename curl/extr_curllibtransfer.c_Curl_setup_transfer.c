#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ multiplex; } ;
struct connectdata {int httpversion; void** sock; TYPE_2__* handler; void* writesockfd; void* sockfd; TYPE_1__ bits; } ;
struct SingleRequest {int getheader; int /*<<< orphan*/  keepon; int /*<<< orphan*/  exp100; int /*<<< orphan*/  start100; struct HTTP* protop; int /*<<< orphan*/  header; scalar_t__ size; } ;
struct HTTP {scalar_t__ sending; } ;
struct TYPE_8__ {scalar_t__ expect100header; } ;
struct TYPE_7__ {int /*<<< orphan*/  expect_100_timeout; int /*<<< orphan*/  opt_no_body; } ;
struct Curl_easy {TYPE_4__ state; TYPE_3__ set; struct SingleRequest req; struct connectdata* conn; } ;
typedef  scalar_t__ curl_off_t ;
struct TYPE_6__ {int protocol; } ;

/* Variables and functions */
 void* CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_expire (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  Curl_pgrsSetDownloadSize (struct Curl_easy*,scalar_t__) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  EXP100_AWAITING_CONTINUE ; 
 int /*<<< orphan*/  EXP100_SENDING_REQUEST ; 
 int /*<<< orphan*/  EXPIRE_100_TIMEOUT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HTTPSEND_BODY ; 
 int /*<<< orphan*/  KEEP_RECV ; 
 int /*<<< orphan*/  KEEP_SEND ; 
 int PROTO_FAMILY_HTTP ; 

void
Curl_setup_transfer(
  struct Curl_easy *data,   /* transfer */
  int sockindex,            /* socket index to read from or -1 */
  curl_off_t size,          /* -1 if unknown at this point */
  bool getheader,           /* TRUE if header parsing is wanted */
  int writesockindex        /* socket index to write to, it may very well be
                               the same we read from. -1 disables */
  )
{
  struct SingleRequest *k = &data->req;
  struct connectdata *conn = data->conn;
  DEBUGASSERT(conn != NULL);
  DEBUGASSERT((sockindex <= 1) && (sockindex >= -1));

  if(conn->bits.multiplex || conn->httpversion == 20) {
    /* when multiplexing, the read/write sockets need to be the same! */
    conn->sockfd = sockindex == -1 ?
      ((writesockindex == -1 ? CURL_SOCKET_BAD : conn->sock[writesockindex])) :
      conn->sock[sockindex];
    conn->writesockfd = conn->sockfd;
  }
  else {
    conn->sockfd = sockindex == -1 ?
      CURL_SOCKET_BAD : conn->sock[sockindex];
    conn->writesockfd = writesockindex == -1 ?
      CURL_SOCKET_BAD:conn->sock[writesockindex];
  }
  k->getheader = getheader;

  k->size = size;

  /* The code sequence below is placed in this function just because all
     necessary input is not always known in do_complete() as this function may
     be called after that */

  if(!k->getheader) {
    k->header = FALSE;
    if(size > 0)
      Curl_pgrsSetDownloadSize(data, size);
  }
  /* we want header and/or body, if neither then don't do this! */
  if(k->getheader || !data->set.opt_no_body) {

    if(sockindex != -1)
      k->keepon |= KEEP_RECV;

    if(writesockindex != -1) {
      struct HTTP *http = data->req.protop;
      /* HTTP 1.1 magic:

         Even if we require a 100-return code before uploading data, we might
         need to write data before that since the REQUEST may not have been
         finished sent off just yet.

         Thus, we must check if the request has been sent before we set the
         state info where we wait for the 100-return code
      */
      if((data->state.expect100header) &&
         (conn->handler->protocol&PROTO_FAMILY_HTTP) &&
         (http->sending == HTTPSEND_BODY)) {
        /* wait with write until we either got 100-continue or a timeout */
        k->exp100 = EXP100_AWAITING_CONTINUE;
        k->start100 = Curl_now();

        /* Set a timeout for the multi interface. Add the inaccuracy margin so
           that we don't fire slightly too early and get denied to run. */
        Curl_expire(data, data->set.expect_100_timeout, EXPIRE_100_TIMEOUT);
      }
      else {
        if(data->state.expect100header)
          /* when we've sent off the rest of the headers, we must await a
             100-continue but first finish sending the request */
          k->exp100 = EXP100_SENDING_REQUEST;

        /* enable the write bit when we're not waiting for continue */
        k->keepon |= KEEP_SEND;
      }
    } /* if(writesockindex != -1) */
  } /* if(k->getheader || !data->set.opt_no_body) */

}