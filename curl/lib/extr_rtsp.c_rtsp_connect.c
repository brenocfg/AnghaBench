#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rtp_channel; } ;
struct TYPE_5__ {TYPE_1__ rtspc; } ;
struct connectdata {TYPE_2__ proto; struct Curl_easy* data; } ;
struct TYPE_6__ {int rtsp_next_client_CSeq; int rtsp_next_server_CSeq; } ;
struct Curl_easy {TYPE_3__ state; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_http_connect (struct connectdata*,int*) ; 

__attribute__((used)) static CURLcode rtsp_connect(struct connectdata *conn, bool *done)
{
  CURLcode httpStatus;
  struct Curl_easy *data = conn->data;

  httpStatus = Curl_http_connect(conn, done);

  /* Initialize the CSeq if not already done */
  if(data->state.rtsp_next_client_CSeq == 0)
    data->state.rtsp_next_client_CSeq = 1;
  if(data->state.rtsp_next_server_CSeq == 0)
    data->state.rtsp_next_server_CSeq = 1;

  conn->proto.rtspc.rtp_channel = -1;

  return httpStatus;
}