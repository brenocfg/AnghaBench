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
struct smtp_conn {scalar_t__ state; scalar_t__ ssldone; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_ssl_connect_nonblocking (struct connectdata*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 scalar_t__ SMTP_UPGRADETLS ; 
 int /*<<< orphan*/  smtp_perform_ehlo (struct connectdata*) ; 
 int /*<<< orphan*/  smtp_to_smtps (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,scalar_t__) ; 

__attribute__((used)) static CURLcode smtp_perform_upgrade_tls(struct connectdata *conn)
{
  /* Start the SSL connection */
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  CURLcode result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET,
                                                 &smtpc->ssldone);

  if(!result) {
    if(smtpc->state != SMTP_UPGRADETLS)
      state(conn, SMTP_UPGRADETLS);

    if(smtpc->ssldone) {
      smtp_to_smtps(conn);
      result = smtp_perform_ehlo(conn);
    }
  }

  return result;
}