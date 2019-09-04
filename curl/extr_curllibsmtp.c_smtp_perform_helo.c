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
struct TYPE_4__ {int /*<<< orphan*/  authused; } ;
struct smtp_conn {int /*<<< orphan*/  domain; int /*<<< orphan*/  pp; TYPE_2__ sasl; } ;
struct TYPE_3__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SASL_AUTH_NONE ; 
 int /*<<< orphan*/  SMTP_HELO ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_perform_helo(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;

  smtpc->sasl.authused = SASL_AUTH_NONE; /* No authentication mechanism used
                                            in smtp connections */

  /* Send the HELO command */
  result = Curl_pp_sendf(&smtpc->pp, "HELO %s", smtpc->domain);

  if(!result)
    state(conn, SMTP_HELO);

  return result;
}