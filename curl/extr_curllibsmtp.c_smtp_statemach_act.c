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
struct pingpong {scalar_t__ sendleft; } ;
struct smtp_conn {int state; struct pingpong pp; } ;
struct TYPE_3__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; int /*<<< orphan*/ * sock; } ;
struct TYPE_4__ {int httpcode; } ;
struct Curl_easy {TYPE_2__ info; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_flushsend (struct pingpong*) ; 
 scalar_t__ Curl_pp_moredata (struct pingpong*) ; 
 scalar_t__ Curl_pp_readresp (int /*<<< orphan*/ ,struct pingpong*,int*,size_t*) ; 
 size_t FIRSTSOCKET ; 
#define  SMTP_AUTH 138 
#define  SMTP_COMMAND 137 
#define  SMTP_DATA 136 
#define  SMTP_EHLO 135 
#define  SMTP_HELO 134 
#define  SMTP_MAIL 133 
#define  SMTP_POSTDATA 132 
#define  SMTP_QUIT 131 
#define  SMTP_RCPT 130 
#define  SMTP_SERVERGREET 129 
#define  SMTP_STARTTLS 128 
 int SMTP_STOP ; 
 int SMTP_UPGRADETLS ; 
 scalar_t__ smtp_perform_upgrade_tls (struct connectdata*) ; 
 scalar_t__ smtp_state_auth_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_command_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_data_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_ehlo_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_helo_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_mail_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_postdata_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_rcpt_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_servergreet_resp (struct connectdata*,int,int) ; 
 scalar_t__ smtp_state_starttls_resp (struct connectdata*,int,int) ; 
 int /*<<< orphan*/  state (struct connectdata*,int) ; 

__attribute__((used)) static CURLcode smtp_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  struct Curl_easy *data = conn->data;
  int smtpcode;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  struct pingpong *pp = &smtpc->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not SMTP */
  if(smtpc->state == SMTP_UPGRADETLS)
    return smtp_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

  do {
    /* Read the response from the server */
    result = Curl_pp_readresp(sock, pp, &smtpcode, &nread);
    if(result)
      return result;

    /* Store the latest response for later retrieval if necessary */
    if(smtpc->state != SMTP_QUIT && smtpcode != 1)
      data->info.httpcode = smtpcode;

    if(!smtpcode)
      break;

    /* We have now received a full SMTP server response */
    switch(smtpc->state) {
    case SMTP_SERVERGREET:
      result = smtp_state_servergreet_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_EHLO:
      result = smtp_state_ehlo_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_HELO:
      result = smtp_state_helo_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_STARTTLS:
      result = smtp_state_starttls_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH:
      result = smtp_state_auth_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_COMMAND:
      result = smtp_state_command_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_MAIL:
      result = smtp_state_mail_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_RCPT:
      result = smtp_state_rcpt_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_DATA:
      result = smtp_state_data_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_POSTDATA:
      result = smtp_state_postdata_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, SMTP_STOP);
      break;
    }
  } while(!result && smtpc->state != SMTP_STOP && Curl_pp_moredata(pp));

  return result;
}