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
struct pop3_conn {scalar_t__ state; scalar_t__ ssldone; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_ssl_connect_nonblocking (struct connectdata*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 scalar_t__ POP3_UPGRADETLS ; 
 int /*<<< orphan*/  pop3_perform_capa (struct connectdata*) ; 
 int /*<<< orphan*/  pop3_to_pop3s (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,scalar_t__) ; 

__attribute__((used)) static CURLcode pop3_perform_upgrade_tls(struct connectdata *conn)
{
  /* Start the SSL connection */
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  CURLcode result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET,
                                                 &pop3c->ssldone);

  if(!result) {
    if(pop3c->state != POP3_UPGRADETLS)
      state(conn, POP3_UPGRADETLS);

    if(pop3c->ssldone) {
      pop3_to_pop3s(conn);
      result = pop3_perform_capa(conn);
    }
  }

  return result;
}