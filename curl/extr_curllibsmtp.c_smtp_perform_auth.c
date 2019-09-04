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
struct smtp_conn {int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static CURLcode smtp_perform_auth(struct connectdata *conn,
                                  const char *mech,
                                  const char *initresp)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;

  if(initresp) {                                  /* AUTH <mech> ...<crlf> */
    /* Send the AUTH command with the initial response */
    result = Curl_pp_sendf(&smtpc->pp, "AUTH %s %s", mech, initresp);
  }
  else {
    /* Send the AUTH command */
    result = Curl_pp_sendf(&smtpc->pp, "AUTH %s", mech);
  }

  return result;
}