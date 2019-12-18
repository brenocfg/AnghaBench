#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tempbuf {int /*<<< orphan*/ * buf; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct connectdata {struct Curl_easy* data; } ;
struct SingleRequest {int keepon; } ;
struct TYPE_2__ {unsigned int tempcount; int /*<<< orphan*/  done; struct tempbuf* tempwrite; } ;
struct Curl_easy {TYPE_1__ state; scalar_t__ multi; struct connectdata* conn; struct SingleRequest req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int CURLPAUSE_RECV ; 
 int CURLPAUSE_SEND ; 
 int /*<<< orphan*/  Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_expire (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_update_timer (scalar_t__) ; 
 int /*<<< orphan*/  Curl_updatesocket (struct Curl_easy*) ; 
 int /*<<< orphan*/  EXPIRE_RUN_NOW ; 
 int KEEP_RECV_PAUSE ; 
 int KEEP_SEND_PAUSE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

CURLcode curl_easy_pause(struct Curl_easy *data, int action)
{
  struct SingleRequest *k = &data->req;
  CURLcode result = CURLE_OK;

  /* first switch off both pause bits */
  int newstate = k->keepon &~ (KEEP_RECV_PAUSE| KEEP_SEND_PAUSE);

  /* set the new desired pause bits */
  newstate |= ((action & CURLPAUSE_RECV)?KEEP_RECV_PAUSE:0) |
    ((action & CURLPAUSE_SEND)?KEEP_SEND_PAUSE:0);

  /* put it back in the keepon */
  k->keepon = newstate;

  if(!(newstate & KEEP_RECV_PAUSE) && data->state.tempcount) {
    /* there are buffers for sending that can be delivered as the receive
       pausing is lifted! */
    unsigned int i;
    unsigned int count = data->state.tempcount;
    struct tempbuf writebuf[3]; /* there can only be three */
    struct connectdata *conn = data->conn;
    struct Curl_easy *saved_data = NULL;

    /* copy the structs to allow for immediate re-pausing */
    for(i = 0; i < data->state.tempcount; i++) {
      writebuf[i] = data->state.tempwrite[i];
      data->state.tempwrite[i].buf = NULL;
    }
    data->state.tempcount = 0;

    /* set the connection's current owner */
    if(conn->data != data) {
      saved_data = conn->data;
      conn->data = data;
    }

    for(i = 0; i < count; i++) {
      /* even if one function returns error, this loops through and frees all
         buffers */
      if(!result)
        result = Curl_client_write(conn, writebuf[i].type, writebuf[i].buf,
                                   writebuf[i].len);
      free(writebuf[i].buf);
    }

    /* recover previous owner of the connection */
    if(saved_data)
      conn->data = saved_data;

    if(result)
      return result;
  }

  /* if there's no error and we're not pausing both directions, we want
     to have this handle checked soon */
  if((newstate & (KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) !=
     (KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) {
    Curl_expire(data, 0, EXPIRE_RUN_NOW); /* get this handle going again */
    if(data->multi)
      Curl_update_timer(data->multi);
  }

  if(!data->state.done)
    /* This transfer may have been moved in or out of the bundle, update the
       corresponding socket callback, if used */
    Curl_updatesocket(data);

  return result;
}