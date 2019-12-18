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
struct TYPE_5__ {scalar_t__ proxy_connect_closed; } ;
struct connectdata {TYPE_4__* given; TYPE_3__* data; TYPE_1__ bits; } ;
struct TYPE_8__ {int protocol; } ;
struct TYPE_6__ {scalar_t__ haproxyprotocol; } ;
struct TYPE_7__ {TYPE_2__ set; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CONNECT_FIRSTSOCKET_PROXY_SSL () ; 
 scalar_t__ CURLE_OK ; 
 int CURLPROTO_HTTPS ; 
 scalar_t__ Curl_connect_ongoing (struct connectdata*) ; 
 scalar_t__ Curl_proxy_connect (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 int TRUE ; 
 scalar_t__ add_haproxy_protocol_header (struct connectdata*) ; 
 int /*<<< orphan*/  connkeep (struct connectdata*,char*) ; 
 scalar_t__ https_connecting (struct connectdata*,int*) ; 

CURLcode Curl_http_connect(struct connectdata *conn, bool *done)
{
  CURLcode result;

  /* We default to persistent connections. We set this already in this connect
     function to make the re-use checks properly be able to check this bit. */
  connkeep(conn, "HTTP default");

  /* the CONNECT procedure might not have been completed */
  result = Curl_proxy_connect(conn, FIRSTSOCKET);
  if(result)
    return result;

  if(conn->bits.proxy_connect_closed)
    /* this is not an error, just part of the connection negotiation */
    return CURLE_OK;

  if(CONNECT_FIRSTSOCKET_PROXY_SSL())
    return CURLE_OK; /* wait for HTTPS proxy SSL initialization to complete */

  if(Curl_connect_ongoing(conn))
    /* nothing else to do except wait right now - we're not done here. */
    return CURLE_OK;

#ifndef CURL_DISABLE_PROXY
  if(conn->data->set.haproxyprotocol) {
    /* add HAProxy PROXY protocol header */
    result = add_haproxy_protocol_header(conn);
    if(result)
      return result;
  }
#endif

  if(conn->given->protocol & CURLPROTO_HTTPS) {
    /* perform SSL initialization */
    result = https_connecting(conn, done);
    if(result)
      return result;
  }
  else
    *done = TRUE;

  return CURLE_OK;
}