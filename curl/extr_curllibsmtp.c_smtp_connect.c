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
struct pingpong {struct connectdata* conn; int /*<<< orphan*/  endofresp; int /*<<< orphan*/  statemach_act; int /*<<< orphan*/  response_time; } ;
struct smtp_conn {int /*<<< orphan*/  sasl; struct pingpong pp; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_init (struct pingpong*) ; 
 int /*<<< orphan*/  Curl_sasl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  RESP_TIMEOUT ; 
 int /*<<< orphan*/  SMTP_SERVERGREET ; 
 int /*<<< orphan*/  connkeep (struct connectdata*,char*) ; 
 int /*<<< orphan*/  saslsmtp ; 
 int /*<<< orphan*/  smtp_endofresp ; 
 scalar_t__ smtp_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ smtp_parse_url_options (struct connectdata*) ; 
 scalar_t__ smtp_parse_url_path (struct connectdata*) ; 
 int /*<<< orphan*/  smtp_statemach_act ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_connect(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  struct pingpong *pp = &smtpc->pp;

  *done = FALSE; /* default to not done yet */

  /* We always support persistent connections in SMTP */
  connkeep(conn, "SMTP default");

  /* Set the default response time-out */
  pp->response_time = RESP_TIMEOUT;
  pp->statemach_act = smtp_statemach_act;
  pp->endofresp = smtp_endofresp;
  pp->conn = conn;

  /* Initialize the SASL storage */
  Curl_sasl_init(&smtpc->sasl, &saslsmtp);

  /* Initialise the pingpong layer */
  Curl_pp_init(pp);

  /* Parse the URL options */
  result = smtp_parse_url_options(conn);
  if(result)
    return result;

  /* Parse the URL path */
  result = smtp_parse_url_path(conn);
  if(result)
    return result;

  /* Start off waiting for the server greeting response */
  state(conn, SMTP_SERVERGREET);

  result = smtp_multi_statemach(conn, done);

  return result;
}