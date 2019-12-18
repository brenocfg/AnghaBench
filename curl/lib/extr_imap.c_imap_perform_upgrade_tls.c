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
struct imap_conn {scalar_t__ state; scalar_t__ ssldone; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_ssl_connect_nonblocking (struct connectdata*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 scalar_t__ IMAP_UPGRADETLS ; 
 int /*<<< orphan*/  imap_perform_capability (struct connectdata*) ; 
 int /*<<< orphan*/  imap_to_imaps (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,scalar_t__) ; 

__attribute__((used)) static CURLcode imap_perform_upgrade_tls(struct connectdata *conn)
{
  /* Start the SSL connection */
  struct imap_conn *imapc = &conn->proto.imapc;
  CURLcode result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET,
                                                 &imapc->ssldone);

  if(!result) {
    if(imapc->state != IMAP_UPGRADETLS)
      state(conn, IMAP_UPGRADETLS);

    if(imapc->ssldone) {
      imap_to_imaps(conn);
      result = imap_perform_capability(conn);
    }
  }

  return result;
}