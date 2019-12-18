#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* retry; scalar_t__ reuse; } ;
struct connectdata {TYPE_5__* handler; TYPE_4__ bits; struct Curl_easy* data; } ;
struct TYPE_12__ {scalar_t__ bytecount; scalar_t__ headerbytecount; scalar_t__ writebytecount; } ;
struct TYPE_9__ {int /*<<< orphan*/  url; } ;
struct TYPE_8__ {void* refused_stream; } ;
struct TYPE_7__ {scalar_t__ rtspreq; int /*<<< orphan*/  opt_no_body; scalar_t__ upload; } ;
struct Curl_easy {TYPE_6__ req; TYPE_3__ change; TYPE_2__ state; TYPE_1__ set; } ;
struct TYPE_11__ {int protocol; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int CURLPROTO_RTSP ; 
 scalar_t__ Curl_readrewind (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 void* FALSE ; 
 int PROTO_FAMILY_HTTP ; 
 scalar_t__ RTSPREQ_RECEIVE ; 
 void* TRUE ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

CURLcode Curl_retry_request(struct connectdata *conn,
                            char **url)
{
  struct Curl_easy *data = conn->data;
  bool retry = FALSE;
  *url = NULL;

  /* if we're talking upload, we can't do the checks below, unless the protocol
     is HTTP as when uploading over HTTP we will still get a response */
  if(data->set.upload &&
     !(conn->handler->protocol&(PROTO_FAMILY_HTTP|CURLPROTO_RTSP)))
    return CURLE_OK;

  if((data->req.bytecount + data->req.headerbytecount == 0) &&
      conn->bits.reuse &&
      (!data->set.opt_no_body
        || (conn->handler->protocol & PROTO_FAMILY_HTTP)) &&
      (data->set.rtspreq != RTSPREQ_RECEIVE))
    /* We got no data, we attempted to re-use a connection. For HTTP this
       can be a retry so we try again regardless if we expected a body.
       For other protocols we only try again only if we expected a body.

       This might happen if the connection was left alive when we were
       done using it before, but that was closed when we wanted to read from
       it again. Bad luck. Retry the same request on a fresh connect! */
    retry = TRUE;
  else if(data->state.refused_stream &&
          (data->req.bytecount + data->req.headerbytecount == 0) ) {
    /* This was sent on a refused stream, safe to rerun. A refused stream
       error can typically only happen on HTTP/2 level if the stream is safe
       to issue again, but the nghttp2 API can deliver the message to other
       streams as well, which is why this adds the check the data counters
       too. */
    infof(conn->data, "REFUSED_STREAM, retrying a fresh connect\n");
    data->state.refused_stream = FALSE; /* clear again */
    retry = TRUE;
  }
  if(retry) {
    infof(conn->data, "Connection died, retrying a fresh connect\n");
    *url = strdup(conn->data->change.url);
    if(!*url)
      return CURLE_OUT_OF_MEMORY;

    connclose(conn, "retry"); /* close this connection */
    conn->bits.retry = TRUE; /* mark this as a connection we're about
                                to retry. Marking it this way should
                                prevent i.e HTTP transfers to return
                                error just because nothing has been
                                transferred! */


    if(conn->handler->protocol&PROTO_FAMILY_HTTP) {
      if(data->req.writebytecount) {
        CURLcode result = Curl_readrewind(conn);
        if(result) {
          Curl_safefree(*url);
          return result;
        }
      }
    }
  }
  return CURLE_OK;
}