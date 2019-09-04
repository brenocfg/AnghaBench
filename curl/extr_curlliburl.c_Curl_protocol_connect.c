#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* protoconnstart; scalar_t__ httpproxy; scalar_t__ tunnel_proxy; scalar_t__* tcpconnect; } ;
struct connectdata {TYPE_2__ bits; TYPE_1__* handler; } ;
struct TYPE_3__ {scalar_t__ (* connect_it ) (struct connectdata*,int*) ;int /*<<< orphan*/  connecting; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CONNECT_FIRSTSOCKET_PROXY_SSL () ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_connect_ongoing (struct connectdata*) ; 
 scalar_t__ Curl_proxy_connect (struct connectdata*,size_t) ; 
 int FALSE ; 
 size_t FIRSTSOCKET ; 
 void* TRUE ; 
 scalar_t__ stub1 (struct connectdata*,int*) ; 

CURLcode Curl_protocol_connect(struct connectdata *conn,
                               bool *protocol_done)
{
  CURLcode result = CURLE_OK;

  *protocol_done = FALSE;

  if(conn->bits.tcpconnect[FIRSTSOCKET] && conn->bits.protoconnstart) {
    /* We already are connected, get back. This may happen when the connect
       worked fine in the first call, like when we connect to a local server
       or proxy. Note that we don't know if the protocol is actually done.

       Unless this protocol doesn't have any protocol-connect callback, as
       then we know we're done. */
    if(!conn->handler->connecting)
      *protocol_done = TRUE;

    return CURLE_OK;
  }

  if(!conn->bits.protoconnstart) {

    result = Curl_proxy_connect(conn, FIRSTSOCKET);
    if(result)
      return result;

    if(CONNECT_FIRSTSOCKET_PROXY_SSL())
      /* wait for HTTPS proxy SSL initialization to complete */
      return CURLE_OK;

    if(conn->bits.tunnel_proxy && conn->bits.httpproxy &&
       Curl_connect_ongoing(conn))
      /* when using an HTTP tunnel proxy, await complete tunnel establishment
         before proceeding further. Return CURLE_OK so we'll be called again */
      return CURLE_OK;

    if(conn->handler->connect_it) {
      /* is there a protocol-specific connect() procedure? */

      /* Call the protocol-specific connect function */
      result = conn->handler->connect_it(conn, protocol_done);
    }
    else
      *protocol_done = TRUE;

    /* it has started, possibly even completed but that knowledge isn't stored
       in this bit! */
    if(!result)
      conn->bits.protoconnstart = TRUE;
  }

  return result; /* pass back status */
}