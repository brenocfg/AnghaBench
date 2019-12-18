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
struct TYPE_5__ {void* do_more; } ;
struct connectdata {TYPE_2__* handler; TYPE_1__ bits; } ;
struct SingleRequest {void* ignorebody; int /*<<< orphan*/  hbufp; int /*<<< orphan*/  buf; scalar_t__ bytecount; int /*<<< orphan*/  header; int /*<<< orphan*/  start; int /*<<< orphan*/  now; } ;
struct TYPE_8__ {int /*<<< orphan*/  headerbuff; int /*<<< orphan*/  buffer; void* expect100header; void* done; void* wildcardmatch; } ;
struct TYPE_7__ {scalar_t__ httpreq; scalar_t__ opt_no_body; } ;
struct Curl_easy {TYPE_4__ state; TYPE_3__ set; struct SingleRequest req; } ;
struct TYPE_6__ {int flags; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  Curl_pgrsSetDownloadCounter (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadCounter (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_speedinit (struct Curl_easy*) ; 
 void* FALSE ; 
 scalar_t__ HTTPREQ_GET ; 
 scalar_t__ HTTPREQ_HEAD ; 
 int PROTOPT_WILDCARD ; 
 int /*<<< orphan*/  TRUE ; 

CURLcode Curl_init_do(struct Curl_easy *data, struct connectdata *conn)
{
  struct SingleRequest *k = &data->req;

  if(conn) {
    conn->bits.do_more = FALSE; /* by default there's no curl_do_more() to
                                   use */
    /* if the protocol used doesn't support wildcards, switch it off */
    if(data->state.wildcardmatch &&
       !(conn->handler->flags & PROTOPT_WILDCARD))
      data->state.wildcardmatch = FALSE;
  }

  data->state.done = FALSE; /* *_done() is not called yet */
  data->state.expect100header = FALSE;


  if(data->set.opt_no_body)
    /* in HTTP lingo, no body means using the HEAD request... */
    data->set.httpreq = HTTPREQ_HEAD;
  else if(HTTPREQ_HEAD == data->set.httpreq)
    /* ... but if unset there really is no perfect method that is the
       "opposite" of HEAD but in reality most people probably think GET
       then. The important thing is that we can't let it remain HEAD if the
       opt_no_body is set FALSE since then we'll behave wrong when getting
       HTTP. */
    data->set.httpreq = HTTPREQ_GET;

  k->start = Curl_now(); /* start time */
  k->now = k->start;   /* current time is now */
  k->header = TRUE; /* assume header */

  k->bytecount = 0;

  k->buf = data->state.buffer;
  k->hbufp = data->state.headerbuff;
  k->ignorebody = FALSE;

  Curl_speedinit(data);

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);

  return CURLE_OK;
}