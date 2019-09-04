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
struct imap_conn {int /*<<< orphan*/  resptag; int /*<<< orphan*/  sasl; int /*<<< orphan*/  preftype; struct pingpong pp; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_init (struct pingpong*) ; 
 int /*<<< orphan*/  Curl_sasl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  IMAP_SERVERGREET ; 
 int /*<<< orphan*/  IMAP_TYPE_ANY ; 
 int /*<<< orphan*/  RESP_TIMEOUT ; 
 int /*<<< orphan*/  connkeep (struct connectdata*,char*) ; 
 int /*<<< orphan*/  imap_endofresp ; 
 scalar_t__ imap_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ imap_parse_url_options (struct connectdata*) ; 
 int /*<<< orphan*/  imap_statemach_act ; 
 int /*<<< orphan*/  saslimap ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static CURLcode imap_connect(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;
  struct pingpong *pp = &imapc->pp;

  *done = FALSE; /* default to not done yet */

  /* We always support persistent connections in IMAP */
  connkeep(conn, "IMAP default");

  /* Set the default response time-out */
  pp->response_time = RESP_TIMEOUT;
  pp->statemach_act = imap_statemach_act;
  pp->endofresp = imap_endofresp;
  pp->conn = conn;

  /* Set the default preferred authentication type and mechanism */
  imapc->preftype = IMAP_TYPE_ANY;
  Curl_sasl_init(&imapc->sasl, &saslimap);

  /* Initialise the pingpong layer */
  Curl_pp_init(pp);

  /* Parse the URL options */
  result = imap_parse_url_options(conn);
  if(result)
    return result;

  /* Start off waiting for the server greeting response */
  state(conn, IMAP_SERVERGREET);

  /* Start off with an response id of '*' */
  strcpy(imapc->resptag, "*");

  result = imap_multi_statemach(conn, done);

  return result;
}