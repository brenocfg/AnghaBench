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
struct pingpong {scalar_t__ sendleft; } ;
struct imap_conn {int state; struct pingpong pp; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_WEIRD_SERVER_REPLY ; 
 scalar_t__ Curl_pp_flushsend (struct pingpong*) ; 
 scalar_t__ Curl_pp_moredata (struct pingpong*) ; 
 scalar_t__ Curl_pp_readresp (int /*<<< orphan*/ ,struct pingpong*,int*,size_t*) ; 
 size_t FIRSTSOCKET ; 
#define  IMAP_APPEND 140 
#define  IMAP_APPEND_FINAL 139 
#define  IMAP_AUTHENTICATE 138 
#define  IMAP_CAPABILITY 137 
#define  IMAP_FETCH 136 
#define  IMAP_FETCH_FINAL 135 
#define  IMAP_LIST 134 
#define  IMAP_LOGIN 133 
#define  IMAP_LOGOUT 132 
#define  IMAP_SEARCH 131 
#define  IMAP_SELECT 130 
#define  IMAP_SERVERGREET 129 
#define  IMAP_STARTTLS 128 
 int IMAP_STOP ; 
 int IMAP_UPGRADETLS ; 
 scalar_t__ imap_perform_upgrade_tls (struct connectdata*) ; 
 scalar_t__ imap_state_append_final_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_append_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_auth_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_capability_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_fetch_final_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_fetch_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_listsearch_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_login_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_select_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_servergreet_resp (struct connectdata*,int,int) ; 
 scalar_t__ imap_state_starttls_resp (struct connectdata*,int,int) ; 
 int /*<<< orphan*/  state (struct connectdata*,int) ; 

__attribute__((used)) static CURLcode imap_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int imapcode;
  struct imap_conn *imapc = &conn->proto.imapc;
  struct pingpong *pp = &imapc->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not IMAP */
  if(imapc->state == IMAP_UPGRADETLS)
    return imap_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

  do {
    /* Read the response from the server */
    result = Curl_pp_readresp(sock, pp, &imapcode, &nread);
    if(result)
      return result;

    /* Was there an error parsing the response line? */
    if(imapcode == -1)
      return CURLE_WEIRD_SERVER_REPLY;

    if(!imapcode)
      break;

    /* We have now received a full IMAP server response */
    switch(imapc->state) {
    case IMAP_SERVERGREET:
      result = imap_state_servergreet_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_CAPABILITY:
      result = imap_state_capability_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_STARTTLS:
      result = imap_state_starttls_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE:
      result = imap_state_auth_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LOGIN:
      result = imap_state_login_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LIST:
    case IMAP_SEARCH:
      result = imap_state_listsearch_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_SELECT:
      result = imap_state_select_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_FETCH:
      result = imap_state_fetch_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_FETCH_FINAL:
      result = imap_state_fetch_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_APPEND:
      result = imap_state_append_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_APPEND_FINAL:
      result = imap_state_append_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LOGOUT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, IMAP_STOP);
      break;
    }
  } while(!result && imapc->state != IMAP_STOP && Curl_pp_moredata(pp));

  return result;
}