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
struct connectdata {int dummy; } ;
struct SingleRequest {int dummy; } ;
struct TYPE_2__ {int maxdownload; } ;
struct Curl_easy {int /*<<< orphan*/  conn; TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CONN_INUSE (struct connectdata*) ; 
 scalar_t__ CURLE_NO_CONNECTION_AVAILABLE ; 
 int /*<<< orphan*/  Curl_attach_connnection (struct Curl_easy*,struct connectdata*) ; 
 int /*<<< orphan*/  Curl_disconnect (struct Curl_easy*,struct connectdata*,int) ; 
 int /*<<< orphan*/  Curl_free_request_state (struct Curl_easy*) ; 
 scalar_t__ Curl_setup_conn (struct connectdata*,int*) ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ create_conn (struct Curl_easy*,struct connectdata**,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

CURLcode Curl_connect(struct Curl_easy *data,
                      bool *asyncp,
                      bool *protocol_done)
{
  CURLcode result;
  struct connectdata *conn;

  *asyncp = FALSE; /* assume synchronous resolves by default */

  /* init the single-transfer specific data */
  Curl_free_request_state(data);
  memset(&data->req, 0, sizeof(struct SingleRequest));
  data->req.maxdownload = -1;

  /* call the stuff that needs to be called */
  result = create_conn(data, &conn, asyncp);

  if(!result) {
    if(CONN_INUSE(conn))
      /* multiplexed */
      *protocol_done = TRUE;
    else if(!*asyncp) {
      /* DNS resolution is done: that's either because this is a reused
         connection, in which case DNS was unnecessary, or because DNS
         really did finish already (synch resolver/fast async resolve) */
      result = Curl_setup_conn(conn, protocol_done);
    }
  }

  if(result == CURLE_NO_CONNECTION_AVAILABLE) {
    return result;
  }
  else if(result && conn) {
    /* We're not allowed to return failure with memory left allocated in the
       connectdata struct, free those here */
    Curl_disconnect(data, conn, TRUE);
  }
  else if(!result && !data->conn)
    /* FILE: transfers already have the connection attached */
    Curl_attach_connnection(data, conn);

  return result;
}