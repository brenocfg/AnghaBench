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
struct pop3_conn {int /*<<< orphan*/  sasl; int /*<<< orphan*/  preftype; struct pingpong pp; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_init (struct pingpong*) ; 
 int /*<<< orphan*/  Curl_sasl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  POP3_SERVERGREET ; 
 int /*<<< orphan*/  POP3_TYPE_ANY ; 
 int /*<<< orphan*/  RESP_TIMEOUT ; 
 int /*<<< orphan*/  connkeep (struct connectdata*,char*) ; 
 int /*<<< orphan*/  pop3_endofresp ; 
 scalar_t__ pop3_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ pop3_parse_url_options (struct connectdata*) ; 
 int /*<<< orphan*/  pop3_statemach_act ; 
 int /*<<< orphan*/  saslpop3 ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_connect(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  *done = FALSE; /* default to not done yet */

  /* We always support persistent connections in POP3 */
  connkeep(conn, "POP3 default");

  /* Set the default response time-out */
  pp->response_time = RESP_TIMEOUT;
  pp->statemach_act = pop3_statemach_act;
  pp->endofresp = pop3_endofresp;
  pp->conn = conn;

  /* Set the default preferred authentication type and mechanism */
  pop3c->preftype = POP3_TYPE_ANY;
  Curl_sasl_init(&pop3c->sasl, &saslpop3);

  /* Initialise the pingpong layer */
  Curl_pp_init(pp);

  /* Parse the URL options */
  result = pop3_parse_url_options(conn);
  if(result)
    return result;

  /* Start off waiting for the server greeting response */
  state(conn, POP3_SERVERGREET);

  result = pop3_multi_statemach(conn, done);

  return result;
}