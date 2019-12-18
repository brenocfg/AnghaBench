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
struct pop3_conn {int state; struct pingpong pp; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_flushsend (struct pingpong*) ; 
 scalar_t__ Curl_pp_moredata (struct pingpong*) ; 
 scalar_t__ Curl_pp_readresp (int /*<<< orphan*/ ,struct pingpong*,int*,size_t*) ; 
 size_t FIRSTSOCKET ; 
#define  POP3_APOP 136 
#define  POP3_AUTH 135 
#define  POP3_CAPA 134 
#define  POP3_COMMAND 133 
#define  POP3_PASS 132 
#define  POP3_QUIT 131 
#define  POP3_SERVERGREET 130 
#define  POP3_STARTTLS 129 
 int POP3_STOP ; 
 int POP3_UPGRADETLS ; 
#define  POP3_USER 128 
 scalar_t__ pop3_perform_upgrade_tls (struct connectdata*) ; 
 scalar_t__ pop3_state_apop_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_auth_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_capa_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_command_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_pass_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_servergreet_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_starttls_resp (struct connectdata*,int,int) ; 
 scalar_t__ pop3_state_user_resp (struct connectdata*,int,int) ; 
 int /*<<< orphan*/  state (struct connectdata*,int) ; 

__attribute__((used)) static CURLcode pop3_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int pop3code;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not POP3 */
  if(pop3c->state == POP3_UPGRADETLS)
    return pop3_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

 do {
    /* Read the response from the server */
    result = Curl_pp_readresp(sock, pp, &pop3code, &nread);
    if(result)
      return result;

    if(!pop3code)
      break;

    /* We have now received a full POP3 server response */
    switch(pop3c->state) {
    case POP3_SERVERGREET:
      result = pop3_state_servergreet_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_CAPA:
      result = pop3_state_capa_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_STARTTLS:
      result = pop3_state_starttls_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH:
      result = pop3_state_auth_resp(conn, pop3code, pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_APOP:
      result = pop3_state_apop_resp(conn, pop3code, pop3c->state);
      break;
#endif

    case POP3_USER:
      result = pop3_state_user_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_PASS:
      result = pop3_state_pass_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_COMMAND:
      result = pop3_state_command_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, POP3_STOP);
      break;
    }
  } while(!result && pop3c->state != POP3_STOP && Curl_pp_moredata(pp));

  return result;
}