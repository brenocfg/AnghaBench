#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void** tcpconnect; void* proxy_connect_closed; } ;
struct TYPE_9__ {int /*<<< orphan*/  uagent; } ;
struct connectdata {scalar_t__* sock; void* now; TYPE_7__ bits; TYPE_6__* handler; TYPE_5__* ssl; int /*<<< orphan*/  dns_entry; TYPE_2__ allocptr; struct Curl_easy* data; } ;
struct TYPE_11__ {scalar_t__ crlf_conversions; } ;
struct TYPE_10__ {scalar_t__ headerbytecount; } ;
struct TYPE_8__ {scalar_t__* str; } ;
struct Curl_easy {TYPE_4__ state; TYPE_3__ req; TYPE_1__ set; } ;
struct TYPE_13__ {int flags; int protocol; } ;
struct TYPE_12__ {scalar_t__ use; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 scalar_t__ Curl_connecthost (struct connectdata*,int /*<<< orphan*/ ) ; 
 void* Curl_now () ; 
 int /*<<< orphan*/  Curl_pgrsTime (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_updateconninfo (struct connectdata*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_verboseconnect (struct connectdata*) ; 
 void* FALSE ; 
 size_t FIRSTSOCKET ; 
 int PROTOPT_NONETWORK ; 
 int PROTO_FAMILY_SSH ; 
 size_t STRING_USERAGENT ; 
 int /*<<< orphan*/  TIMER_APPCONNECT ; 
 int /*<<< orphan*/  TIMER_CONNECT ; 
 int /*<<< orphan*/  TIMER_NAMELOOKUP ; 
 void* TRUE ; 
 int /*<<< orphan*/  aprintf (char*,scalar_t__) ; 

CURLcode Curl_setup_conn(struct connectdata *conn,
                         bool *protocol_done)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  Curl_pgrsTime(data, TIMER_NAMELOOKUP);

  if(conn->handler->flags & PROTOPT_NONETWORK) {
    /* nothing to setup when not using a network */
    *protocol_done = TRUE;
    return result;
  }
  *protocol_done = FALSE; /* default to not done */

  /* set proxy_connect_closed to false unconditionally already here since it
     is used strictly to provide extra information to a parent function in the
     case of proxy CONNECT failures and we must make sure we don't have it
     lingering set from a previous invoke */
  conn->bits.proxy_connect_closed = FALSE;

  /*
   * Set user-agent. Used for HTTP, but since we can attempt to tunnel
   * basically anything through a http proxy we can't limit this based on
   * protocol.
   */
  if(data->set.str[STRING_USERAGENT]) {
    Curl_safefree(conn->allocptr.uagent);
    conn->allocptr.uagent =
      aprintf("User-Agent: %s\r\n", data->set.str[STRING_USERAGENT]);
    if(!conn->allocptr.uagent)
      return CURLE_OUT_OF_MEMORY;
  }

  data->req.headerbytecount = 0;

#ifdef CURL_DO_LINEEND_CONV
  data->state.crlf_conversions = 0; /* reset CRLF conversion counter */
#endif /* CURL_DO_LINEEND_CONV */

  /* set start time here for timeout purposes in the connect procedure, it
     is later set again for the progress meter purpose */
  conn->now = Curl_now();

  if(CURL_SOCKET_BAD == conn->sock[FIRSTSOCKET]) {
    conn->bits.tcpconnect[FIRSTSOCKET] = FALSE;
    result = Curl_connecthost(conn, conn->dns_entry);
    if(result)
      return result;
  }
  else {
    Curl_pgrsTime(data, TIMER_CONNECT);    /* we're connected already */
    if(conn->ssl[FIRSTSOCKET].use ||
       (conn->handler->protocol & PROTO_FAMILY_SSH))
      Curl_pgrsTime(data, TIMER_APPCONNECT); /* we're connected already */
    conn->bits.tcpconnect[FIRSTSOCKET] = TRUE;
    *protocol_done = TRUE;
    Curl_updateconninfo(conn, conn->sock[FIRSTSOCKET]);
    Curl_verboseconnect(conn);
  }

  conn->now = Curl_now(); /* time this *after* the connect is done, we set
                             this here perhaps a second time */
  return result;
}